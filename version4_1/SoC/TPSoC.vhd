LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;
ENTITY TPSoC IS
	PORT (
		CLOCK_50 : IN STD_LOGIC;
		KEY 	: IN STD_LOGIC_VECTOR (0 DOWNTO 0);
		SW  	: IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		LED	: OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
		DRAM_CLK, DRAM_CKE : OUT STD_LOGIC;
		DRAM_ADDR : OUT STD_LOGIC_VECTOR(12 DOWNTO 0);
		DRAM_BA : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
		DRAM_CS_N, DRAM_CAS_N, DRAM_RAS_N, DRAM_WE_N, MTR_Sleep_n: OUT STD_LOGIC;
		MTRR_N,MTRL_N,MTRR_P,MTRL_P  : OUT STD_LOGIC;
		DRAM_DQ : INOUT STD_LOGIC_VECTOR(15 DOWNTO 0);
		DRAM_DQM : OUT STD_LOGIC_VECTOR(1 DOWNTO 0)
	);
END TPSoC;


ARCHITECTURE SoC_l OF TPSoC IS
SIGNAL s_nr, s_nl, s_pl, s_pr : std_logic;
COMPONENT nios_sys
	PORT (
		clk_clk               : in  std_logic                    := 'X';             -- clk
      leds_connexion_export : out std_logic_vector(7 downto 0);                    -- export
      sws_connexion_export  : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
      reset_reset_n         : in  std_logic                    := 'X';              -- reset_
		sd_ram_wire_addr      : out   std_logic_vector(12 downto 0);                    -- addr
		sd_ram_wire_ba        : out   std_logic_vector(1 downto 0);                     -- ba
		sd_ram_wire_cas_n     : out   std_logic;                                        -- cas_n
		sd_ram_wire_cke       : out   std_logic;                                        -- cke
		sd_ram_wire_cs_n      : out   std_logic;                                        -- cs_n
		sd_ram_wire_dq        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
		sd_ram_wire_dqm       : out   std_logic_vector(1 downto 0);                     -- dqm
		sd_ram_wire_ras_n     : out   std_logic;                                        -- ras_n
		sd_ram_wire_we_n      : out   std_logic ;                                        -- we_n
		to_hex_export         : out   std_logic_vector(15 downto 0) ;                    -- export
		m_nr_export            : out   std_logic;                                        -- export
		m_nl_export            : out   std_logic;                                        -- export
		m_pl_export            : out   std_logic;                                        -- export
		m_pr_export            : out   std_logic                                         -- export
);
END COMPONENT;

BEGIN
NiosII : nios_sys
	PORT MAP(
		clk_clk => CLOCK_50,
		reset_reset_n => KEY(0),
		sws_connexion_export => SW(3 DOWNTO 0),
		--leds_connexion_export => LED(7 DOWNTO 0),
		sd_ram_wire_addr      => DRAM_ADDR,      --    sd_ram_wire.addr
		sd_ram_wire_ba        => DRAM_BA,        --               .ba
		sd_ram_wire_cas_n     => DRAM_CAS_N,     --               .cas_n
		sd_ram_wire_cke       => DRAM_CKE,       --               .cke
		sd_ram_wire_cs_n      => DRAM_CS_N,      --               .cs_n
		sd_ram_wire_dq        => DRAM_DQ,        --               .dq
		sd_ram_wire_dqm       => DRAM_DQM,       --               .dqm
		sd_ram_wire_ras_n     => DRAM_RAS_N,     --               .ras_n
		sd_ram_wire_we_n      => DRAM_WE_N,       --               .we_n
		--to_hex_export(7 DOWNTO 0)         => LED(7 DOWNTO 0),          --         to_hex.export
		m_nr_export          => s_nr,
	   m_nl_export          => s_nl,
	   m_pl_export          => s_pl,
	   m_pr_export          => s_pr
);

MTRR_N <= s_nr;
MTRL_N <= s_nl;
MTRR_P <= s_pr; -- Attention: dans ton code précédent tu avais inversé P et L
MTRL_P <= s_pl;

 -- ==========================================
 -- 2. VISUALISATION SUR LES LEDS (DEBUG)
 -- ==========================================
LED(4) <= s_nr; -- Droit N
LED(3) <= s_pr; -- Droit P
LED(5) <= s_nl; -- Gauche N
LED(2) <= s_pl; -- Gauche P
LED(7 downto 6) <= "00"; -- Éteindre les autres
LED(1 downto 0) <= "00";

 -- ==========================================
 -- 3. ACTIVATION ELECTRIQUE (INDISPENSABLE)
 -- ==========================================
MTR_Sleep_n    <= '1'; -- Réveille le driver
END SoC_l;