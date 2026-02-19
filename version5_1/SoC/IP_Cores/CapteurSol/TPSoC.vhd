LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY TPSoC IS
    PORT (
        CLOCK_50 : IN STD_LOGIC;
        KEY      : IN STD_LOGIC_VECTOR (0 DOWNTO 0); -- Reset
        SW       : IN STD_LOGIC_VECTOR (7 DOWNTO 0); -- Réglage du Seuil
        LED      : OUT STD_LOGIC_VECTOR(7 DOWNTO 0); -- Affichage Capteurs
        
        -- SDRAM (On les laisse pour éviter les erreurs de pins, mais inutilisés)
        DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
        DRAM_ADDR : OUT STD_LOGIC_VECTOR(12 DOWNTO 0);
        DRAM_BA   : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
        DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
        DRAM_DQ   : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
        DRAM_DQM  : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
        
        -- MOTEURS (On force l'arrêt pour ce test)
        MTR_Sleep_n    : OUT STD_LOGIC; 
        VCC3P3_PWRON_n : OUT STD_LOGIC;
        MTRR_N, MTRL_N, MTRR_P, MTRL_P : OUT STD_LOGIC;

        -- ADC CAPTEURS (Nouveaux signaux !)
        ADC_CONVST : OUT STD_LOGIC;
        ADC_SCK    : OUT STD_LOGIC;
        ADC_SDI    : OUT STD_LOGIC;
        ADC_SDO    : IN STD_LOGIC
    );
END TPSoC;

ARCHITECTURE Test_Direct OF TPSoC IS

    COMPONENT capteurs_sol_seuil
    PORT (
        clk          : in  std_logic;
        reset_n      : in  std_logic;
        data_capture : in  std_logic;
        data_readyr  : out std_logic;
        
        -- Données brutes (optionnel, on ne s'en sert pas ici)
        data0r, data1r, data2r, data3r, data4r, data5r, data6r : out std_logic_vector(7 downto 0);
        
        -- Réglages et Résultat
        NIVEAU       : in std_logic_vector(7 downto 0);
        vect_capt    : out std_logic_vector(6 downto 0);
        
        -- SPI ADC
        ADC_CONVSTr  : out std_logic;
        ADC_SCK      : out std_logic;
        ADC_SDIr     : out std_logic;
        ADC_SDO      : in  std_logic 
    );
    END COMPONENT;

    SIGNAL s_resultat_capteurs : STD_LOGIC_VECTOR(6 DOWNTO 0);

BEGIN

    -- Instanciation directe du module capteur
    U_TEST_CAPTEURS : capteurs_sol_seuil
    PORT MAP (
        clk          => CLOCK_50,
        reset_n      => KEY(0),
        data_capture => '1', -- Capture en continu
        data_readyr  => open,
        
        -- Connexion au Switches pour régler la sensibilité en direct
        NIVEAU       => SW, 
        
        -- Résultat vers signal interne
        vect_capt    => s_resultat_capteurs,
        
        -- Signaux physiques vers l'ADC
        ADC_CONVSTr  => ADC_CONVST,
        ADC_SCK      => ADC_SCK,
        ADC_SDIr     => ADC_SDI,
        ADC_SDO      => ADC_SDO,
        
        -- Ports inutilisés
        data0r => open, data1r => open, data2r => open, 
        data3r => open, data4r => open, data5r => open, data6r => open
    );

    -- Affichage sur les LEDs
    -- LED 0 à 6 affichent l'état des 7 capteurs
    LED(6 DOWNTO 0) <= s_resultat_capteurs;
    LED(7) <= '0'; -- Eteinte

    -- Gestion Moteurs (Arrêtés mais Carte Alimentée)
    MTR_Sleep_n    <= '1'; 
    VCC3P3_PWRON_n <= '0'; -- IMPORTANT : Alimente aussi les LEDs Infrarouges !
    
    MTRR_N <= '0'; MTRL_N <= '0';
    MTRR_P <= '0'; MTRL_P <= '0';
    
    -- SDRAM Clock (Juste pour éviter warning)
    DRAM_CLK <= CLOCK_50;

END Test_Direct;