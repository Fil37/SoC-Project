// --- A. LECTURE CAPTEURS ---
        IOWR(ADC_CORE_0_BASE, 0, 180); // Seuil de luminosité (A ajuster)
        usleep(10); 
        int val_capt = IORD(ADC_CORE_0_BASE, 0) & 0x7F; // On garde les 7 bits (0 à 6)

        // --- B. CALCUL PPU / PDU (Selon PDF p.8) ---
        int PPU = -1; // Position Premier Un (Initialisé à "pas trouvé")
        int PDU = -1; // Position Dernier Un

        // On parcourt les bits de 0 (Droite) à 6 (Gauche)
        for (int i = 0; i < 7; i++) {
            // On vérifie si le bit 'i' est à 1 (Ligne détectée)
            if ((val_capt >> i) & 1) {
                
                // Si c'est le tout premier '1' qu'on croise, c'est le PPU
                if (PPU == -1) {
                    PPU = i; 
                }
                
                // On met à jour le PDU à chaque fois qu'on voit un '1'.
                // À la fin de la boucle, PDU vaudra bien l'index du dernier '1'.
                PDU = i;
            }
        }

        // --- C. CALCUL DE L'ERREUR ---
        // Cas 1 : La ligne est vue (PPU et PDU ont été modifiés)
        if (PPU != -1) {
            // Formule du PDF : PPU + PDU - 6
            // Résultat entre -6 (Tout à gauche) et +6 (Tout à droite)
            // 0 signifie centré (car 3 + 3 - 6 = 0)
            erreur = PPU + PDU - 6;
        } 
        // Cas 2 : Ligne perdue (val_capt == 0)
        else {
            // On garde la dernière erreur connue pour continuer le virage
            erreur = erreur_prec;
        }

        // --- D. CALCUL PID (Classique) ---
        integrale = integrale + erreur;
        
        // Anti-Windup (Important pour éviter l'accumulation)
        if (integrale > 500) integrale = 500;
        if (integrale < -500) integrale = -500;

        derivee = erreur - erreur_prec;
        
        // Calcul final de la correction
        // Note : Avec cette méthode, l'erreur max est 6.
        // Il faudra peut-être augmenter ton Kp par rapport à avant.
        correction_pid = (Kp * erreur) + (Ki * integrale) + (Kd * derivee);
        
        erreur_prec = erreur;

        // --- E. COMMANDE MOTEUR ---
        // (Appelle ici ta fonction 'piloter_physique' ou similaire)