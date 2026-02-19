LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY PWM_avalon_interface IS
PORT (
    -- Interface Avalon (Communication avec le processeur)
    clock, resetn : IN STD_LOGIC;
    read, write, chipselect : IN STD_LOGIC;
    writedata : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    readdata : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
    
    -- Interface Conduit (Sorties vers les moteurs externes)
    dc_motor_p_R, dc_motor_n_R : OUT STD_LOGIC;
    dc_motor_p_L, dc_motor_n_L : OUT STD_LOGIC
);
END PWM_avalon_interface;

ARCHITECTURE arch OF PWM_avalon_interface IS

    -- Déclaration du composant PWM_generation fourni
    COMPONENT PWM_generation
    PORT(
        clk, reset_n : in std_logic;
        s_writedataR, s_writedataL : in std_logic_vector(13 downto 0);        
        dc_motor_p_R, dc_motor_n_R, dc_motor_p_L, dc_motor_n_L : out std_logic
    );
    END COMPONENT;

    -- Signaux internes
    signal s_command : std_logic_vector(13 downto 0);

BEGIN

    -- 1. Gestion de l'écriture (Bus Avalon -> Signal interne)
    -- On récupère les bits utiles (0 à 13) du bus de données
    process(clock, resetn)
    begin
        if resetn = '0' then
            s_command <= (others => '0');
        elsif rising_edge(clock) then
            if chipselect = '1' and write = '1' then
                s_command <= writedata(13 downto 0);
            end if;
        end if;
    end process;

    -- 2. Instanciation du module PWM (Le cœur du système)
    -- Note : On envoie la même commande (s_command) à Gauche (L) et Droite (R)
    -- pour cette étape de validation simple.
    pwm_inst : PWM_generation
    PORT MAP (
        clk => clock,
        reset_n => resetn,
        s_writedataR => s_command, -- Commande Moteur Droit
        s_writedataL => s_command, -- Commande Moteur Gauche
        dc_motor_p_R => dc_motor_p_R,
        dc_motor_n_R => dc_motor_n_R,
        dc_motor_p_L => dc_motor_p_L,
        dc_motor_n_L => dc_motor_n_L
    );

    -- 3. Lecture (Optionnel mais recommandé par le protocole Avalon)
    -- On renvoie ce qu'on a écrit (avec des 0 sur les bits 15-14 inutilisés)
    readdata <= "00" & s_command;

END arch;