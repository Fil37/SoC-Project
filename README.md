# Line follower — robot suiveur de ligne sur SoC FPGA

Projet de robotique embarquée réalisé autour d’une carte **Terasic DE0-Nano (Cyclone IV E, EP4CE22F17C6)**. Le robot suit une ligne et peut explorer un labyrinthe grâce à une chaîne de traitement combinant logique programmable et logiciel embarqué.

## Architecture

- **SoC construit avec Qsys / Platform Designer** : processeur Nios II, SDRAM et interconnexions Avalon-MM.
- **Matériel personnalisé en VHDL** : interfaces de capteurs de sol, conversion/seuillage ADC, registres Avalon et génération PWM pour les deux moteurs. Les quatre composants recensés dans les itérations sont CapteurSol, ADC_Core, reg_16 et PWM.
- **Commande embarquée en C bare-metal** : acquisition de **7 capteurs infrarouges** et régulation PID avec une boucle visée à **200 Hz**.
- **FPGA** : intégration des interfaces, du PWM et des signaux d’E/S de la DE0-Nano.

## Organisation du dépôt

- `version1/` à `version5_1/` : différentes itérations du projet ; chaque dossier n’est pas nécessairement une version autonome ou complète.
- `version*/SoC/` : projets Quartus, fichiers Qsys, top-level VHDL et composants matériels (dont `IP_Cores/` dans les versions concernées).
- `version*/SoC/software/` et dossiers de programmes associés : logiciels et fichiers de support Nios II.
- `calibration.c`, `seuil.c`, `noir.txt` et `seuillage.xlsx` : éléments liés aux essais de calibration et de détection.
- `TP/` : documents et ressources de travaux pratiques conservés dans le dépôt.

## Outils et reprise du projet

Les fichiers Quartus/Qsys du dépôt ont été générés avec l’écosystème Intel/Altera. Pour examiner une itération, ouvrir son fichier `.qpf` dans le dossier `version*/SoC/` avec une version compatible de Quartus, puis ouvrir le système Qsys correspondant. Le logiciel Nios II se construit séparément avec l’environnement Nios II EDS/BSP associé à cette configuration.

Les versions historiques contiennent aussi des fichiers `.bak`, des rapports et des binaires générés. Les sources du projet sont à privilégier ; la compilation complète n’a pas été vérifiée dans un environnement Quartus reproductible.

## Technologies

VHDL · C bare-metal · Intel Quartus · Qsys / Platform Designer · Nios II · Avalon-MM · SDRAM · PWM · PID
