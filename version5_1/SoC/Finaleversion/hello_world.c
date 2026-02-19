#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "io.h"
#include "system.h"

/* --- 1. REGLAGES PHYSIQUES (Validés) --- */
#define DEADZONE 1950        // Seuil de démarrage
#define TRIM_DROIT 1.18      // Le moteur droit force plus
#define PWM_MAX 3125         

/* --- 2. REGLAGES VITESSE & PID --- */
// Vitesse modérée pour commencer (ni trop lente, ni trop rapide)
#define VITESSE_BASE 300 

// Gains PID (Pour supprimer l'oscillation)
float Kp = 40.0;    // Si ça oscille trop, baisse à 50
float Ki = 0.2;     // On laisse à 0 pour l'instant (simplifie)
float Kd = 1200.0;   // Le "Frein" qui empêche de dépasser la ligne
float Kp_enerve =120;
/* --- 3. FONCTIONS BAS NIVEAU --- */
unsigned int preparer_moteur(int marche, int arriere, int vitesse) {
    unsigned int cmd = 0;
    if (vitesse > PWM_MAX) vitesse = PWM_MAX;
    if (vitesse < 0) vitesse = 0;
    if (marche) {
        cmd |= (1 << 13);
        if (arriere) cmd |= (1 << 12);
        cmd |= (vitesse & 0xFFF);
    }
    return cmd;
}

void envoyer_commande_physique(int pwm_G, int pwm_D) {
    int vG = abs(pwm_G); int dG = (pwm_G >= 0) ? 0 : 1;
    int vD = abs(pwm_D); int dD = (pwm_D >= 0) ? 0 : 1;
    
    unsigned int cmd_G = preparer_moteur(1, dG, vG);
    unsigned int cmd_D = preparer_moteur(1, dD, vD);
    IOWR(PWM_COMPONENT_0_BASE, 0, (cmd_G << 14) | (cmd_D & 0x3FFF));
}

void piloter_progressif(int cmd_G, int cmd_D) {
    int final_G = 0, final_D = 0;
    int cmd_D_trimee;

    // Ajout de la Deadzone (Zone morte)
    if (cmd_G > 0) final_G = cmd_G + DEADZONE;
    else if (cmd_G < 0) final_G = cmd_G - DEADZONE;

    cmd_D_trimee = (int)(cmd_D * TRIM_DROIT);
    if (cmd_D_trimee > 0) final_D = cmd_D_trimee + DEADZONE;
    else if (cmd_D_trimee < 0) final_D = cmd_D_trimee - DEADZONE;

    envoyer_commande_physique(final_G, final_D);
}

/* --- 4. MAIN --- */
int main() {
    int val_capt;
    float erreur = 0, erreur_prec = 0;
    float derivee = 0;
    float correction = 0;
    int i, PPU, PDU;
    int consigne_G, consigne_D;
	float integrale = 0;
	int vitesse_actuelle = VITESSE_BASE;
    printf("--- MODE PID LISSE (Signes Corriges) ---\n");
    IOWR(ADC_CORE_0_BASE, 0, 110); 
    usleep(1000);

    while(1) {
        // --- A. Lecture Capteurs ---
        val_capt = IORD(ADC_CORE_0_BASE, 0) & 0x7F;
        
        PPU = -1; PDU = -1;
        for (i = 0; i < 7; i++) {
            if ((val_capt >> i) & 1) {
                if (PPU == -1) PPU = i;
                PDU = i;
            }
        }

        if (PPU != -1) erreur = (float)(PPU + PDU - 6);
        else erreur = erreur_prec;

        // --- B. Calcul PID ---
        derivee = erreur - erreur_prec;
		integrale = integrale + erreur;
		if (integrale > 500) integrale = 500;
        if (integrale < -500) integrale = -500;
		
        if(abs((int)erreur)>=3){
			Kp = Kp_enerve;
		}
		if(abs((int)erreur)<=1){
			vitesse_actuelle = VITESSE_BASE + 200;
		}
        // Calcul simple PD (Proportionnel + Dérivé)
		if((erreur>0&& erreur_prec<0) || (erreur<0 &&erreur_prec >0)){
			integrale =0;
		}
		
        correction = (Kp * erreur) + (Kd * derivee)+ (Ki*integrale);
        
        erreur_prec = erreur;
		
        // --- C. Mixage Moteurs (LA CLE DU SUCCES) ---
        // Dans ton Bang-Bang :
        // Si Erreur > 0 (Gauche) -> Tu mettais Droite=Vite, Gauche=Lent
        // Donc Correction positive doit ACCELERER Droite et RALENTIR Gauche.
        
        consigne_G = vitesse_actuelle - (int)correction; 
        consigne_D = vitesse_actuelle + (int)correction; 

        // --- D. Envoi ---
        piloter_progressif(consigne_G, consigne_D);
        
        usleep(5000); 
    }
    return 0;
}