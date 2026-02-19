library ieee;
use ieee.std_logic_1164.all;

entity Test_Robot_Hardcoded is
    port(
        -- Entrée Horloge (Nom exact du QSF)
        CLOCK_50 : in std_logic;                   
        
        -- Sorties Ponts en H (Noms exacts du QSF)
        MTRR_P, MTRR_N : out std_logic;            
        MTRL_P, MTRL_N : out std_logic;            
        
        -- Signal de réveil du Driver Moteur (Nom exact du QSF)
        MTR_Sleep_n    : out std_logic            
    );
end entity;

architecture bhv of Test_Robot_Hardcoded is

    component PWM_generation
        port(
            clk, reset_n : in std_logic;
            s_writedataR, s_writedataL : in std_logic_vector(13 downto 0);      
            dc_motor_p_R, dc_motor_n_R : out std_logic;
            dc_motor_p_L, dc_motor_n_L : out std_logic
        );
    end component;

    -- Signaux internes
    signal cmd_R, cmd_L : std_logic_vector(13 downto 0);
    signal internal_reset_n : std_logic; -- Pour remplacer le bouton

begin

    -- ====================================================
    -- 1. Configuration (Reset désactivé & Commandes)
    -- ====================================================
    
    -- On force le reset à '1' pour que le système fonctionne tout le temps
    internal_reset_n <= '1';

    -- Configuration Moteurs : Avancer
    -- Bit 13 = '1' (GO)
    -- Bit 12 = '0' (Forward)
    -- Bits 11-0 = "100111000100" (Valeur décimale 2500 sur 3125 max => ~80% de puissance)
    
    cmd_R <= "10100111000100"; 
    cmd_L <= "10100111000100";

    -- ====================================================
    -- 2. Instantiation du module PWM
    -- ====================================================
    U_PWM : PWM_generation
    port map(
        clk          => CLOCK_50,
        reset_n      => internal_reset_n, -- Connecté au signal fixe '1'
        s_writedataR => cmd_R,
        s_writedataL => cmd_L,
        dc_motor_p_R => MTRR_P,     
        dc_motor_n_R => MTRR_N,
        dc_motor_p_L => MTRL_P,
        dc_motor_n_L => MTRL_N
    );

    -- ====================================================
    -- 3. Activation du Driver (DRV8848)
    -- ====================================================
    -- Nécessaire pour sortir le driver du mode veille (Sleep Mode)
    MTR_Sleep_n <= '1'; 
    
    -- Note: Le signal VCC3P3_PWRON_n n'est pas piloté ici.
    -- Les sorties PWM bougeront, mais si la carte fille coupe l'alimentation
    -- des moteurs faute de signal PWRON, les roues ne tourneront pas.

end architecture;