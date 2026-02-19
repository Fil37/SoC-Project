library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity PWM_generation is
    port(
        clk, reset_n : in std_logic;
        -- Bit 13: Go(1)/Stop(0)
        -- Bit 12: Forward(0)/Backward(1)
        -- Bits 11-0: Vitesse
        s_writedataR, s_writedataL : in std_logic_vector(13 downto 0);      
        dc_motor_p_R, dc_motor_n_R : out std_logic;
        dc_motor_p_L, dc_motor_n_L : out std_logic
    );
end entity;

architecture arch of PWM_generation is
    constant freqfpga : integer := 50000000; -- 50 MHz [cite: 68]
    constant freqpwm  : integer := 16000;    -- 16 kHz
    signal PWMr, PWMl : std_logic;
    signal tick       : unsigned(31 downto 0) := (others => '0');
    signal total_dur  : unsigned(31 downto 0); -- Changé en unsigned pour simplifier
begin

    total_dur <= to_unsigned(freqfpga/freqpwm, 32);

    process(clk, reset_n)
    begin
        if reset_n = '0' then
            tick <= (others => '0');
            PWMr <= '0';
            PWMl <= '0';
        elsif rising_edge(clk) then
            if tick >= total_dur then
                tick <= (others => '0');
                PWMr <= '1'; -- Début du cycle : état haut
                PWMl <= '1';
            else    
                tick <= tick + 1;
                -- Fin de l'impulsion pour le moteur droit
                if tick >= unsigned(s_writedataR(11 downto 0)) then
                    PWMr <= '0';
                end if;
                -- Fin de l'impulsion pour le moteur gauche
                if tick >= unsigned(s_writedataL(11 downto 0)) then
                    PWMl <= '0';
                end if;
            end if;
        end if;
    end process;

    -- Logique de commande des ponts en H (DRV8848)
    -- Moteur Droit
    dc_motor_p_R <= PWMr when (s_writedataR(13)='1' and s_writedataR(12)='0') else '0';
    dc_motor_n_R <= PWMr when (s_writedataR(13)='1' and s_writedataR(12)='1') else '0';

    -- Moteur Gauche
    dc_motor_p_L <= PWMl when (s_writedataL(13)='1' and s_writedataL(12)='0') else '0';
    dc_motor_n_L <= PWMl when (s_writedataL(13)='1' and s_writedataL(12)='1') else '0';

end architecture arch;