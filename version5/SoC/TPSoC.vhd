LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY TPSoC IS
    PORT (
        CLOCK_50 : IN STD_LOGIC;
        KEY      : IN STD_LOGIC_VECTOR (1 DOWNTO 0); -- [cite: 1045]
        SW       : IN STD_LOGIC_VECTOR (3 DOWNTO 0); -- [cite: 1046]
        LED      : OUT STD_LOGIC_VECTOR(7 DOWNTO 0); -- [cite: 1044]
        
        -- SDRAM pins [cite: 1047, 1048, 1049]
        DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
        DRAM_ADDR : OUT STD_LOGIC_VECTOR(12 DOWNTO 0);
        DRAM_BA   : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
        DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N : OUT STD_LOGIC;
        DRAM_DQ   : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
        DRAM_DQM  : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
        
        -- MOTEURS pins [cite: 1051, 1052]
        MTR_Sleep_n    : OUT STD_LOGIC; 
        VCC3P3_PWRON_n : OUT STD_LOGIC;
        MTRR_N, MTRL_N, MTRR_P, MTRL_P,IR_LED_ON : OUT STD_LOGIC;

        -- ADC CAPTEURS (Noms du QSF pour le robot) 
        LTC_ADC_CONVST : OUT STD_LOGIC;
        LTC_ADC_SCK    : OUT STD_LOGIC;
        LTC_ADC_SDI    : OUT STD_LOGIC;
        LTC_ADC_SDO    : IN  STD_LOGIC
    );
END TPSoC;

ARCHITECTURE SoC_l OF TPSoC IS
    -- Signaux internes pour récupérer les sorties PWM du Nios
    SIGNAL s_nr, s_nl, s_pl, s_pr : std_logic;

    COMPONENT nios_sys
        PORT (
            clk_clk               : in  std_logic;
            reset_reset_n         : in  std_logic;
            sws_connexion_export  : in  std_logic_vector(3 downto 0);
            sd_ram_wire_addr      : out std_logic_vector(12 downto 0);
            sd_ram_wire_ba        : out std_logic_vector(1 downto 0);
            sd_ram_wire_cas_n     : out std_logic;
            sd_ram_wire_cke       : out std_logic;
            sd_ram_wire_cs_n      : out std_logic;
            sd_ram_wire_dq        : inout std_logic_vector(15 downto 0);
            sd_ram_wire_dqm       : out std_logic_vector(1 downto 0);
            sd_ram_wire_ras_n     : out std_logic;
            sd_ram_wire_we_n      : out std_logic;
            m_nr_export           : out std_logic;
            m_nl_export           : out std_logic;
            m_pl_export           : out std_logic;
            m_pr_export           : out std_logic;
            cpt_sol_CONVST        : out std_logic;
            cpt_sol_SCK           : out std_logic;
            cpt_sol_SDI           : out std_logic;
            cpt_sol_SDO           : in  std_logic;
				data_ready_export     : out   std_logic;                                    
				val_capt_export       : out   std_logic_vector(6 downto 0)                      -- export
        );
    END COMPONENT;

BEGIN

NiosII : nios_sys
    PORT MAP(
        clk_clk              => CLOCK_50,
        reset_reset_n        => KEY(0), -- Reset actif à 0 [cite: 1045]
        sws_connexion_export => SW(3 DOWNTO 0),
        
        -- SDRAM [cite: 1049]
        sd_ram_wire_addr     => DRAM_ADDR,
        sd_ram_wire_ba       => DRAM_BA,
        sd_ram_wire_cas_n    => DRAM_CAS_N,
        sd_ram_wire_cke      => DRAM_CKE,
        sd_ram_wire_cs_n     => DRAM_CS_N,
        sd_ram_wire_dq       => DRAM_DQ,
        sd_ram_wire_dqm      => DRAM_DQM,
        sd_ram_wire_ras_n    => DRAM_RAS_N,
        sd_ram_wire_we_n     => DRAM_WE_N,

        -- PWM Moteurs (vers signaux internes)
        m_nr_export          => s_nr,
        m_nl_export          => s_nl,
        m_pl_export          => s_pl,
        m_pr_export          => s_pr,

        -- CAPTEURS (Vers les pins LTC du robot) 
        cpt_sol_CONVST       => LTC_ADC_CONVST,
        cpt_sol_SCK          => LTC_ADC_SCK,
        cpt_sol_SDI          => LTC_ADC_SDI,
        cpt_sol_SDO          => LTC_ADC_SDO,
		  data_ready_export    => LED(0),                                    
		  val_capt_export      => LED(7 downto 1)                      -- export
    );

-- Connexion des moteurs aux broches physiques 
MTRR_N <= s_nr;
MTRL_N <= s_nl;
MTRR_P <= s_pr; 
MTRL_P <= s_pl;

-- Activation électrique du matériel [cite: 215, 613]
MTR_Sleep_n    <= '1'; -- Sortir du mode veille [cite: 215]
VCC3P3_PWRON_n <= '0'; -- Allumer l'alimentation 3.3V 
IR_LED_ON      <= '1';

-- Horloge SDRAM (doit être la même que le système)
DRAM_CLK <= CLOCK_50;

END SoC_l;