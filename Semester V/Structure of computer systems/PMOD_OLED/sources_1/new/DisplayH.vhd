library IEEE; 
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity DisplayH is
    Port ( CLK     : in  STD_LOGIC;
           RST     : in  STD_LOGIC;
           EN      : in  STD_LOGIC;
           CS      : out STD_LOGIC;
           SDO     : out STD_LOGIC;
           SCLK    : out STD_LOGIC;
           DC      : out STD_LOGIC;
           FIN     : out STD_LOGIC);
end DisplayH;

architecture Behavioral of DisplayH is

    signal temp_fin : STD_LOGIC := '0';
    signal temp_cs : STD_LOGIC := '1';
    signal temp_sdo : STD_LOGIC := '0';
    signal temp_sclk : STD_LOGIC := '0';
    signal temp_dc : STD_LOGIC := '1'; -- Data command set to data

    -- Bitmap pentru litera "H"
    type bitmap_array is array (0 to 4) of std_logic_vector(7 downto 0);
        constant H_bitmap: bitmap_array := (
            "11000011", -- Linia 1
            "11000011", -- Linia 2
            "11111111", -- Linia 3
            "11000011", -- Linia 4
            "11000011"  -- Linia 5
        );

    signal bitmap_index : integer range 0 to 4 := 0;

begin

    process(CLK)
    begin
        if rising_edge(CLK) then
            if RST = '1' then
                temp_fin <= '0';
                bitmap_index <= 0;
            elsif EN = '1' then
                temp_dc <= '1'; -- Set to data mode
                temp_cs <= '0'; -- Start transmission
                temp_sdo <= H_bitmap(bitmap_index)(7); -- Send first bit
                bitmap_index <= bitmap_index + 1;
                if bitmap_index > 4 then
                    temp_fin <= '1'; -- Finish transmission
                    temp_cs <= '1'; -- End transmission
                    bitmap_index <= 0;
                end if;
            else
                temp_fin <= '0';
                bitmap_index <= 0;
            end if;
        end if;
    end process;

    CS <= temp_cs;
    SDO <= temp_sdo;
    SCLK <= temp_sclk;
    DC <= temp_dc;
    FIN <= temp_fin;

end Behavioral;
