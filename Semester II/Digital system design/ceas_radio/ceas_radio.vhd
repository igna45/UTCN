library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ceas_radio is
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
end ceas_radio;

architecture comport of ceas_radio is
    signal count_min : integer range 0 to 59 := 0;
    signal count_hour : integer range 0 to 23 := 0;
    signal set_alarm_hour : integer range 0 to 23 := 0;
    signal set_alarm_minute : integer range 0 to 59 := 0;
    signal enable_min : std_logic := '0';
    signal enable_hour : std_logic := '0';
    signal state : integer range 0 to 3 := 0;
    signal count_clk : integer range 0 to 50000000 := 0;
    signal one_second_pulse : std_logic := '0';
begin
    process(clk) --divizor de ceas
    begin
        if rising_edge(clk) then
            if count_clk = 50000000 then
                count_clk <= 0;
                one_second_pulse <= not one_second_pulse;
            else
                count_clk <= count_clk + 1;
            end if;
        end if;
    end process;

    process(one_second_pulse, reset)
    begin
        if reset = '1' then
            count_min <= 0;
            count_hour <= 0;
            set_alarm_hour <= 0;
            set_alarm_minute <= 0;
            enable_min <= '0';
            enable_hour <= '0';
            state <= 0;   --stare asteptare
            bell <= '0';   
            radio <= '0'; 
            current_hour <= to_unsigned(0, 8);
            current_minute <= to_unsigned(0, 8);
        elsif rising_edge(one_second_pulse) then
            case state is
                when 0 =>  --stare asteptare
                    if start = '1' then
                        enable_min <= '1';
                        enable_hour <= '1';
                        state <= 1;
                    end if;
                when 1 =>  --stare ceas pornit
                    if stop = '1' then
                        enable_min <= '0';
                        enable_hour <= '0';
                        state <= 0;
                        bell <= '0';   
                        radio <= '0';  
                    elsif set_alarm = '1' or set_radio = '1' then
                        state <= 2;
                    end if;
                when 2 =>  --stare programare sonerie/radio
                    if start = '1' then
                        if set_alarm = '1' then
                            set_alarm_hour <= to_integer(alarm_hour);
                            set_alarm_minute <= to_integer(alarm_minute);
                        end if;
                        if set_radio = '1' then
                            radio <= '1';
                        end if;
                        state <= 3;
                    else
                        state <= 1;
                    end if;
                when 3 =>  --stare sonerie/radio activa
                    if stop = '1' then
                        bell <= '0';
                        radio <= '0';
                        state <= 1;
                    end if;
                when others =>
                    state <= 0;
            end case;

            if set_time = '1' and (state = 1 or state = 2 or state = 3) then
                if to_integer(set_hour) < 24 and to_integer(set_minute) < 60 then
                    count_hour <= to_integer(set_hour);
                    count_min <= to_integer(set_minute);
                end if;
            end if;

            if enable_min = '1' then
                if count_min = 59 then
                    count_min <= 0;
                    if enable_hour = '1' then
                        if count_hour = 23 then
                            count_hour <= 0;
                        else
                            count_hour <= count_hour + 1;
                        end if;
                    end if;
                else
                    count_min <= count_min + 1;
                end if;
            end if;

            if (bell = '1' or radio = '1') and stop = '1' then
                bell <= '0';
                radio <= '0';
            end if;

            if enable_min = '1' and count_hour = set_alarm_hour and count_min = set_alarm_minute then
				bell <= '1';
            end if;

            current_hour <= to_unsigned(count_hour, 8);
            current_minute <= to_unsigned(count_min, 8);
        end if;
    end process;
end comport;