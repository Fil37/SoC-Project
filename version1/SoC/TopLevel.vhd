LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;
ENTITY TPSoC IS
	PORT (
		CLOCK_50 : IN STD_LOGIC;
		KEY 	: IN STD_LOGIC_VECTOR (0 DOWNTO 0);
		SW  	: IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		LED	: OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
	);
END TPSoC;


ARCHITECTURE SoC_l OF TPSoC IS
COMPONENT nios_sys
	PORT (
		clk_clk               : in  std_logic                    := 'X';             -- clk
      leds_connexion_export : out std_logic_vector(7 downto 0);                    -- export
      sws_connexion_export  : in  std_logic_vector(3 downto 0) := (others => 'X'); -- export
      reset_reset_n         : in  std_logic                    := 'X'              -- reset_
	);
END COMPONENT;
BEGIN
NiosII : nios_sys
	PORT MAP(
		clk_clk => CLOCK_50,
		reset_reset_n => KEY(0),
		sws_connexion_export => SW(3 DOWNTO 0),
		leds_connexion_export => LED(7 DOWNTO 0)
	);
END SoC_l;