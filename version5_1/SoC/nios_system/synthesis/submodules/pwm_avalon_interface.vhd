LIBRARY ieee;
USE ieee.std_logic_1164.all;
ENTITY pwm_avalon_interface IS
PORT ( clock, resetn : IN STD_LOGIC;
	read, write, chipselect : IN STD_LOGIC;
	writedata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	readdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0); 
	dc_motor_p_R,dc_motor_n_R, dc_motor_p_L,dc_motor_n_L: out std_logic
	);
END pwm_avalon_interface;
ARCHITECTURE Structure OF pwm_avalon_interface IS
	SIGNAL s_command_R, s_command_L: STD_LOGIC_VECTOR(15 DOWNTO 0);
	SIGNAL s_command: STD_LOGIC_VECTOR(31 DOWNTO 0);
	
	
	COMPONENT PWM_generation
	port(
		clk,reset_n:in std_logic;
		s_writedataR,s_writedataL: in std_logic_vector(13 downto 0);		
			-- Le bit13 : bit de go(1)/stop(0). 
			-- Le bit12: bit de forward(0)/backward(1). 
			-- Les bits 11 à 0: vitesse=durée état haut
			dc_motor_p_R,dc_motor_n_R, dc_motor_p_L,dc_motor_n_L: out std_logic
			);
	END COMPONENT;
BEGIN
	--reg_R: reg16 PORT MAP (clock, resetn, writedata, "11", s_command_R);
	--reg_L: reg16 PORT MAP (clock, resetn, writedata, "11", s_command_L);
	process(clock, resetn)
    begin
        if resetn = '0' then
            s_command <= (others => '0');
        elsif rising_edge(clock) then
            if chipselect = '1' and write = '1' then
                s_command <= writedata;
            end if;
        end if;
    end process;
	
	pwm_inst : PWM_generation
    PORT MAP (
        clk => clock,
        reset_n => resetn,
        s_writedataR => s_command(13 downto 0), 
        s_writedataL => s_command(27 downto 14), 
        dc_motor_p_R => dc_motor_p_R,
        dc_motor_n_R => dc_motor_n_R,
        dc_motor_p_L => dc_motor_p_L,
        dc_motor_n_L => dc_motor_n_L
    );
	--readdata <= "0000"&s_command_R(13 downto 0)&s_command_L(13 downto 0);
	readdata <= s_command;
END Structure;