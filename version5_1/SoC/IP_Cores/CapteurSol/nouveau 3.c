LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY interface_capteurs IS
PORT (
    clock, resetn : IN STD_LOGIC;
    read, write, chipselect  : IN STD_LOGIC;
    writedata     : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    readdata      : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    ADC_CONVST, ADC_SCK, ADC_SDI : OUT STD_LOGIC;
    ADC_SDO : IN STD_LOGIC;
    vect_capt_out : OUT STD_LOGIC_VECTOR(6 DOWNTO 0)
);
END interface_capteurs;

ARCHITECTURE arch OF interface_capteurs IS

    COMPONENT capteurs_sol_seuil
    PORT (
        clk, reset_n : IN STD_LOGIC;
        data_capture : IN STD_LOGIC; 
        NIVEAU       : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        vect_capt    : OUT STD_LOGIC_VECTOR(6 DOWNTO 0);
        ADC_CONVSTr  : OUT STD_LOGIC;
        ADC_SCK      : OUT STD_LOGIC;
        ADC_SDIr     : OUT STD_LOGIC;
        ADC_SDO      : IN STD_LOGIC
    );
    END COMPONENT;
    
    -- Correction 1 : Il faut donner le nom exact du composant PLL
    COMPONENT pll_2freqs
    PORT (
        areset      : IN STD_LOGIC := '0';
        inclk0      : IN STD_LOGIC := '0';
        c0          : OUT STD_LOGIC;
        c1          : OUT STD_LOGIC 
    );
    END COMPONENT;

    SIGNAL s_niveau : STD_LOGIC_VECTOR(7 DOWNTO 0);
    SIGNAL s_resultat_capteurs : STD_LOGIC_VECTOR(6 DOWNTO 0);
    
    -- Signaux pour la PLL et le Pulse
    SIGNAL s_clock_2Khz : STD_LOGIC;
    SIGNAL s_clock_2Khz_prev : STD_LOGIC; -- Pour détecter le front
    SIGNAL s_capture : STD_LOGIC; 

BEGIN
    
    -- Processus unique synchronisé sur 50MHz (Plus robuste)
    PROCESS(clock, resetn)
    BEGIN
        IF resetn = '0' THEN
            s_niveau <= "10000000"; -- 128 (Moyen)
            s_capture <= '0';
            s_clock_2Khz_prev <= '0';
            
        ELSIF rising_edge(clock) THEN
            -- 1. Gestion de l'écriture du Seuil (CPU)
            IF chipselect = '1' and write = '1' THEN
                s_niveau <= writedata(7 DOWNTO 0);
            END IF;
            
            -- 2. Génération du Pulse de Capture via le 2kHz
            -- On regarde l'état précédent du signal 2kHz
            s_clock_2Khz_prev <= s_clock_2Khz;
            
            -- Si on passe de 0 à 1 (Front Montant du 2kHz)
            IF (s_clock_2Khz_prev = '0' AND s_clock_2Khz = '1') THEN
                s_capture <= '1'; -- On lance l'impulsion
            ELSE
                s_capture <= '0'; -- On coupe tout de suite après
            END IF;
            
        END IF;
    END PROCESS;

    -- Lecture des données
    readdata <= X"000000" & "0" & s_resultat_capteurs;
    vect_capt_out <= s_resultat_capteurs;
     
    -- Instanciation Capteurs
    U_CAPTEURS : capteurs_sol_seuil
    PORT MAP (
        clk          => clock,
        reset_n      => resetn,
        -- Correction 2 : On connecte le signal interne généré par le PLL, plus le CPU
        data_capture => s_capture, 
        
        NIVEAU       => s_niveau,
        vect_capt    => s_resultat_capteurs,
        
        ADC_CONVSTr  => ADC_CONVST,
        ADC_SCK      => ADC_SCK,
        ADC_SDIr     => ADC_SDI,
        ADC_SDO      => ADC_SDO
    );
    
    -- Instanciation PLL
    U_PLL : pll_2freqs
    PORT MAP (
        inclk0  => clock,
        -- Correction 3 : Attention, resetn est actif bas, areset est actif haut !
        areset  => NOT resetn, 
        c1      => s_clock_2Khz
        -- c0 n'est pas utilisé ici, on le laisse ouvert
    );

END arch;