LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.std_logic_unsigned.all; 
USE ieee.numeric_std.all;

ENTITY interface_capteurs IS
PORT (
    clock, resetn : IN STD_LOGIC;
    read, write, chipselect  : IN STD_LOGIC;
    writedata     : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    readdata      : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    
    data_ready  : out std_logic;
    
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
        
        data_readyr : out std_logic;
        data0r      : out std_logic_vector(7 downto 0);
        data1r      : out std_logic_vector(7 downto 0);
        data2r      : out std_logic_vector(7 downto 0);
        data3r      : out std_logic_vector(7 downto 0);
        data4r      : out std_logic_vector(7 downto 0);
        data5r      : out std_logic_vector(7 downto 0);
        data6r      : out std_logic_vector(7 downto 0);
        
        ADC_CONVSTr  : OUT STD_LOGIC;
        ADC_SCK      : OUT STD_LOGIC;
        ADC_SDIr     : OUT STD_LOGIC;
        ADC_SDO      : IN STD_LOGIC
    );
    END COMPONENT;
    
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
    
    -- Signaux PLL
    SIGNAL s_clock_2Khz : STD_LOGIC;
    SIGNAL s_clock_2Khz_prev : STD_LOGIC;
    SIGNAL s_capture : STD_LOGIC; 
    
    SIGNAL s_ready : STD_LOGIC;
    TYPE t_data_array IS ARRAY (0 TO 6) OF STD_LOGIC_VECTOR(7 DOWNTO 0);
    SIGNAL s_data_array : t_data_array;
    

    SIGNAL s_channel_select : INTEGER RANGE 0 TO 7 := 7;

BEGIN
    
    PROCESS(clock, resetn)
    BEGIN
        IF resetn = '0' THEN
            s_niveau <= "10000000"; 
            s_capture <= '0';
            s_clock_2Khz_prev <= '0';
            s_channel_select <= 7;
            
        ELSIF rising_edge(clock) THEN
            
            
            IF chipselect = '1' and write = '1' THEN
                IF unsigned(writedata) <= 6 THEN
                    s_channel_select <= to_integer(unsigned(writedata));
                ELSE
                    s_niveau <= writedata(7 DOWNTO 0);
                    s_channel_select <= 7;
                END IF;
            END IF;
            
            s_clock_2Khz_prev <= s_clock_2Khz;
            IF (s_clock_2Khz_prev = '0' AND s_clock_2Khz = '1') THEN
                s_capture <= '1';
            ELSE
                s_capture <= '0'; 
            END IF;
            
        END IF;
    END PROCESS;

    PROCESS(s_channel_select, s_resultat_capteurs, s_data_array, s_ready)
    BEGIN
        IF s_channel_select = 7 THEN
            readdata <= X"000000" & "0" & s_resultat_capteurs; 
        ELSE
            readdata <= s_ready & X"0000" & "000"&X"0" & s_data_array(s_channel_select);
        END IF;
    END PROCESS;

    vect_capt_out <= s_resultat_capteurs;
    data_ready    <= s_ready; 
     
    U_CAPTEURS : capteurs_sol_seuil
    PORT MAP (
        clk          => clock,
        reset_n      => resetn,
        data_capture => s_capture, 
        NIVEAU       => s_niveau,
        vect_capt    => s_resultat_capteurs,
        
        data_readyr  => s_ready,
        data0r       => s_data_array(0),
        data1r       => s_data_array(1),
        data2r       => s_data_array(2),
        data3r       => s_data_array(3),
        data4r       => s_data_array(4),
        data5r       => s_data_array(5),
        data6r       => s_data_array(6),
        
        ADC_CONVSTr  => ADC_CONVST,
        ADC_SCK      => ADC_SCK,
        ADC_SDIr     => ADC_SDI,
        ADC_SDO      => ADC_SDO
    );
    
    U_PLL : pll_2freqs
    PORT MAP (
        inclk0  => clock,
        areset  => NOT resetn, 
        c1      => s_clock_2Khz
    );

END arch;