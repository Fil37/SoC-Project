#include <stdio.h>
#include <unistd.h>
#include "io.h"
#include "system.h"

/* --- 1. PARAMETRES CALIBRES (NE PAS TOUCHER) --- */
#define DEADZONE 1950         // Votre mesure "En l'air"
#define TRIM_DROIT 1.173     // Votre ratio 1700/1500
#define PWM_MAX 3125         // Plage 16kHz 

/* --- 2. REGLAGES PID (A AJUSTER) --- */
/* Commencez avec Ki=0, Kd=0 et montez Kp */
float Kp = 150.0;  // Puissance de réaction
float Ki = 0.05;   // Correction des erreurs persistantes
float Kd = 1000.0;  // Amortissement (Anticipation)

#define VITESSE_BASE 250 // Vitesse moyenne (doit être > Deadzone)

/* Fonction d'envoi bas niveau avec corrections physiques */
unsigned int preparer_moteur(int marche, int arriere, int vitesse) {
    unsigned int cmd = 0;
    if (vitesse > PWM_MAX) vitesse = PWM_MAX;
    if (vitesse < 0) vitesse = 0;

    if (marche) {
        cmd |= (1 << 13);           // Activation
        if (arriere) cmd |= (1 << 12); // Direction
        cmd |= (vitesse & 0xFFF);   // Vitesse 12 bits
    }
    return cmd;
}

void envoyer_commande(int consigne_G, int consigne_D) {
	int vitesse_abs_G, direction_G;
    int vitesse_abs_D, direction_D;
	if (consigne_G >= 0) {
        direction_G = 0;         
        vitesse_abs_G = consigne_G; 
    } 
    else {
        direction_G = 1;           
        vitesse_abs_G = -consigne_G; 
    }
	if (consigne_D >= 0) {
        direction_D = 0;
        vitesse_abs_D = consigne_D;
    } 
    else {
        direction_D = 1;
        vitesse_abs_D = -consigne_D;
    }
    unsigned int cmd_gauche = preparer_moteur(1, direction_G, vitesse_abs_G);
    unsigned int cmd_droite = preparer_moteur(1, direction_D, vitesse_abs_D);
    
    // Assemblage : Gauche (bits 14-27) | Droite (bits 0-13)
    unsigned int cmd_finale = (cmd_gauche << 14) | (cmd_droite & 0x3FFF);
    IOWR(PWM_COMPONENT_0_BASE, 0, cmd_finale);
}

void piloter_moteurs(int consigne_pid_G, int consigne_pid_D) {
    int cmd_G_finale = 0;
    int cmd_D_finale = 0;

    // 1. MOTEUR GAUCHE (Référence)
    if (consigne_pid_G > 0)      cmd_G_finale = consigne_pid_G + DEADZONE;
    else if (consigne_pid_G < 0) cmd_G_finale = consigne_pid_G - DEADZONE;

    // 2. MOTEUR DROIT (Avec correction de frottement x1.18)
    // On applique le trim sur la commande AVANT d'ajouter la deadzone
    // car le frottement agit sur toute la plage.
    int consigne_D_trimee = (int)(consigne_pid_D * TRIM_DROIT);

    if (consigne_D_trimee > 0)      cmd_D_finale = consigne_D_trimee + DEADZONE;
    else if (consigne_D_trimee < 0) cmd_D_finale = consigne_D_trimee - DEADZONE;

    // 3. SATURATION (Sécurité indispensable)
    if (cmd_G_finale > PWM_MAX) cmd_G_finale = PWM_MAX;
    if (cmd_G_finale < -PWM_MAX) cmd_G_finale = -PWM_MAX;
    
    if (cmd_D_finale > PWM_MAX) cmd_D_finale = PWM_MAX;
    if (cmd_D_finale < -PWM_MAX) cmd_D_finale = -PWM_MAX;

    // 4. ENVOI (On utilise ta fonction envoyer_commande qui gère direction et bits)
    envoyer_commande(cmd_G_finale, cmd_D_finale);
}

int main() {
    int val_capt;
    float erreur = 0, erreur_prec = 0;
    float integrale = 0, derivee = 0;
    float correction_pid;
    int moteur_G, moteur_D;

    printf("--- ROBOT PRET : PID + TRIM 1.133 + DEADZONE 350 ---\n");
	IOWR(ADC_CORE_0_BASE, 0, 110); // Seuil 180 (A ajuster selon lumière)
    usleep(100); 
	
    while(1) {
		 int val_capt = IORD(ADC_CORE_0_BASE, 0) & 0x7F; // On garde les 7 bits (0 à 6)

        int PPU = -1; // Position Premier Un (Initialisé à "pas trouvé")
        int PDU = -1; // Position Dernier Un

        for (int i = 0; i < 7; i++) {
            if ((val_capt >> i) & 1) {
                
                if (PPU == -1) {
                    PPU = i; 
                }
                
                PDU = i;
            }
        }

        if (PPU != -1) {
            erreur = (float)(PPU + PDU - 6);
        } 
        else {
            erreur = erreur_prec;
        }

        integrale = integrale + erreur;
        
        if (integrale > 500) integrale = 500;
        if (integrale < -500) integrale = -500;

        derivee = erreur - erreur_prec;
        
        correction_pid = (Kp * erreur) + (Ki * integrale) + (Kd * derivee);
        
        erreur_prec = erreur;
        moteur_G = VITESSE_BASE + (int)correction_pid;
        moteur_D = VITESSE_BASE - (int)correction_pid;

        piloter_moteurs(moteur_G, moteur_D);

        // Debug (A commenter si le robot est trop lent)
         printf("Err: %.2f | PID: %.0f | G: %d D: %d\r", erreur, correction_pid, moteur_G, moteur_D);
        
        usleep(5000); 
    }
    return 0;
}