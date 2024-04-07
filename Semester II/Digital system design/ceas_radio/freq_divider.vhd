library ieee;
use ieee.std_logic_1164.all;

entity freq_divider is
    port(
        clk : in std_logic;
        reset : in std_logic;
        clk_out : inout std_logic
    );
end freq_divider;

architecture behavior of freq_divider is
    constant N : integer := 500000; -- adjust this value based on your input frequency and desired output frequency
    signal count : integer range 0 to N;
begin
    process(clk, reset)
    begin
        if reset = '1' then
            count <= 0;
            clk_out <= '0';
        elsif rising_edge(clk) then
            if count = N then
                count <= 0;
                clk_out <= not clk_out;
            else
                count <= count + 1;
            end if;
        end if;
    end process;
end behavior;
