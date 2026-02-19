#include <stdio.h>
#include <unistd.h>
#include "io.h"
#include "system.h"

/* --- CONSTANTES --- */
#define PWM_MAX 3125 //

/* Fonction de préparation (identique à votre code actuel) */
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

void envoyer_commande(int vG, int vD) {
    unsigned int cmd_gauche = preparer_moteur(1, 0, vG);
    unsigned int cmd_droite = preparer_moteur(1, 0, vD);
    
    // Assemblage : Gauche (bits 14-27) | Droite (bits 0-13)
    unsigned int cmd_finale = (cmd_gauche << 14) | (cmd_droite & 0x3FFF);
    IOWR(PWM_COMPONENT_0_BASE, 0, cmd_finale);
}

int main() {
    int vG = 1600; // Vitesse Gauche
    int vD = 1600; // Vitesse Droite
    int step = 10; // Pas d'incrément
    char input;
    int mode = 0; // 0=Stop, 1=Test

    printf("\n=== BANC DE TEST MOTEURS CUTE CAR ===\n");
    printf("Controles Clavier (appuyez sur Entree apres chaque touche) :\n");
    printf("  'z' : Augmenter les DEUX moteurs (+%d)\n", step);
    printf("  's' : Diminuer les DEUX moteurs (-%d)\n", step);
    printf("  'q' : Augmenter GAUCHE seulement (Equilibrage)\n");
    printf("  'd' : Augmenter DROIT seulement (Equilibrage)\n");
    printf("  '0' : ARRET D'URGENCE (Vitesse = 0)\n");
    printf("-------------------------------------\n");

    while(1) {
        printf("PWM Actuel -> Gauche: %d | Droite: %d >> ", vG, vD);
        scanf(" %c", &input); // Attente d'une commande utilisateur

        switch(input) {
            case 'z': // Monter vitesse globale (Ramp-up test)
                vG += step; vD += step; 
                break;
            case 's': // Descendre vitesse globale (Ramp-down test)
                vG -= step; vD -= step; 
                if(vG < 0) vG = 0; if(vD < 0) vD = 0;
                break;
            case 'q': // Correction Trim Gauche
                vG += step; 
                break;
            case 'd': // Correction Trim Droit
                vD += step; 
                break;
            case 'w': // Diminuer Gauche seul
                vG -= step; 
                break;
            case 'c': // Diminuer Droit seul
                vD -= step; 
                break;
            case '0': // Reset
                vG = 0; vD = 0;
                break;
        }

        // Sécurité bornes
        if (vG > PWM_MAX) vG = PWM_MAX;
        if (vD > PWM_MAX) vD = PWM_MAX;
        if (vG < 0) vG = 0;
        if (vD < 0) vD = 0;

        envoyer_commande(vG, vD);
    }
    return 0;
}