library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ceas_radio_tb is
end ceas_radio_tb;

architecture tb of ceas_radio_tb is
    signal clk : std_logic := '0';
    signal reset : std_logic := '0';
    signal set_time : std_logic := '0';
    signal set_hour : unsigned(7 downto 0) := (others => '0');
    signal set_minute : unsigned(7 downto 0) := (others => '0');
    signal set_alarm : std_logic := '0';
    signal alarm_hour : unsigned(7 downto 0) := (others => '0');
    signal alarm_minute : unsigned(7 downto 0) := (others => '0');
    signal set_radio : std_logic := '0';
    signal start : std_logic := '0';
    signal stop : std_logic := '0';
    signal bell : std_logic;
    signal radio : std_logic;
    signal current_hour : unsigned(7 downto 0);
    signal current_minute : unsigned(7 downto 0);

    constant clk_period : time := 20 ns;

    component ceas_radio is
        port(
            clk : in std_logic;
            reset : in std_logic;
            set_time : in std_logic;
            set_hour : in unsigned(7 downto 0);
            set_minute : in unsigned(7 downto 0);
            set_alarm : in std_logic;
            alarm_hour : in unsigned(7 downto 0);
            alarm_minute : in unsigned(7 downto 0);
            set_radio : in std_logic;
            start : in std_logic;
            stop : in std_logic;
            bell : inout std_logic;
            radio : inout std_logic;
            current_hour : out unsigned(7 downto 0);
            current_minute : out unsigned(7 downto 0)
        );
    end component;

begin
    DUT : ceas_radio port map (
        clk => clk,
        reset => reset,
        set_time => set_time,
        set_hour => set_hour,
        set_minute => set_minute,
        set_alarm => set_alarm,
        alarm_hour => alarm_hour,
        alarm_minute => alarm_minute,
        set_radio => set_radio,
        start => start,
        stop => stop,
        bell => bell,
        radio => radio,
        current_hour => current_hour,
        current_minute => current_minute
    );

    clk <= not clk after clk_period / 2;

    process
    begin
        --Reset
        reset <= '1'; wait for clk_period * 2;
        reset <= '0'; wait for clk_period * 2;

        --Set time to 20:50
        set_time <= '1'; set_hour <= to_unsigned(20, 8); set_minute <= to_unsigned(50, 8); wait for clk_period * 2;
        set_time <= '0'; wait for clk_period * 2;

        --Start the clock
        start <= '1'; wait for clk_period * 10;

        --Set alarm for 13:00
        set_alarm <= '1'; alarm_hour <= to_unsigned(13, 8); alarm_minute <= to_unsigned(00, 8); wait for clk_period * 2;
        set_alarm <= '0'; wait for clk_period * 2;

        --Stop clock 
        wait for clk_period * 30;
        start <= '0'; wait for clk_period * 2;

        --Change the time to 14:58
        set_time <= '1'; set_hour <= to_unsigned(14, 8); set_minute <= to_unsigned(58, 8); wait for clk_period * 2;
        set_time <= '0'; wait for clk_period * 2;
	
        start <= '1'; wait for clk_period * 10;

        --Set radio
        set_radio <= '1'; wait for clk_period * 2;
        set_radio <= '0'; wait for clk_period * 2;

        --Wait
        wait for clk_period * 30;

        --Set alarm for 15:01
        set_alarm <= '1'; alarm_hour <= to_unsigned(15, 8); alarm_minute <= to_unsigned(01, 8); wait for clk_period * 2;
        set_alarm <= '0'; wait for clk_period * 2;

        --Wait
	   wait until bell = '1'; wait for clk_period * 2;

        --Stop the alarm
        stop <= '1'; wait for clk_period * 2;
        stop <= '0'; wait for clk_period * 2;

        wait;
    end process;
end tb;
