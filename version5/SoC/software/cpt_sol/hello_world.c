#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"

// Remplacez CAPTEURS_BASE par le nom défini dans votre system.h
#define ADDR_CAPTEURS  ADC_CORE_0_BASE

int main() {
    int valeurs_brutes[7];
    int i;

    printf("=== CALIBRATION DES CAPTEURS ===\n");
    printf("1. Posez le robot sur le BLANC.\n");
    printf("2. Regardez les valeurs.\n");
    printf("3. Posez le robot sur le NOIR.\n");
    printf("--------------------------------\n");

    while(1) {
        // Lecture des 7 capteurs un par un
        for(i = 0; i < 7; i++) {
            // 1. On demande au FPGA de sélectionner le capteur i
            // (Le VHDL va diriger data[i] vers readdata)
            IOWR(ADDR_CAPTEURS, 0, i);

            // 2. On lit la valeur (on masque pour garder juste les 8 bits)
            valeurs_brutes[i] = IORD(ADDR_CAPTEURS, 0) & 0xFF;
        }

        // Affichage propre pour le terminal
        printf("C0:%3d | C1:%3d | C2:%3d | C3:%3d | C4:%3d | C5:%3d | C6:%3d\r",
               valeurs_brutes[0], valeurs_brutes[1], valeurs_brutes[2],
               valeurs_brutes[3], valeurs_brutes[4], valeurs_brutes[5], valeurs_brutes[6]);

        usleep(200000); // Pause 200ms pour ne pas spammer le terminal
    }

    return 0;
}
