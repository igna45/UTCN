LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY PmodOLEDCtrl_tb IS
END PmodOLEDCtrl_tb;

ARCHITECTURE behavior OF PmodOLEDCtrl_tb IS 

    COMPONENT PmodOLEDCtrl
        PORT(
            CLK  : IN  std_logic;
            RST  : IN  std_logic;
            CS   : OUT std_logic;
            SDIN : OUT std_logic;
            SCLK : OUT std_logic;
            DC   : OUT std_logic;
            RES  : OUT std_logic;
            VBAT : OUT std_logic;
            VDD  : OUT std_logic
        );
    END COMPONENT;

    SIGNAL CLK  : std_logic := '0';
    SIGNAL RST  : std_logic := '0';

    SIGNAL CS   : std_logic;
    SIGNAL SDIN : std_logic;
    SIGNAL SCLK : std_logic;
    SIGNAL DC   : std_logic;
    SIGNAL RES  : std_logic;
    SIGNAL VBAT : std_logic;
    SIGNAL VDD  : std_logic;

    CONSTANT clk_period : TIME := 10 ns;

BEGIN

    uut: PmodOLEDCtrl PORT MAP (
        CLK  => CLK,
        RST  => RST,
        CS   => CS,
        SDIN => SDIN,
        SCLK => SCLK,
        DC   => DC,
        RES  => RES,
        VBAT => VBAT,
        VDD  => VDD
    );

    clk_process :PROCESS
    BEGIN
        CLK <= '0';
        WAIT FOR clk_period/2;
        CLK <= '1';
        WAIT FOR clk_period/2;
    END PROCESS;

    stim_proc: PROCESS
    BEGIN       
       
        RST <= '1';
        WAIT FOR 20 ns; 
        RST <= '0';

        WAIT; 
    END PROCESS;

END;
