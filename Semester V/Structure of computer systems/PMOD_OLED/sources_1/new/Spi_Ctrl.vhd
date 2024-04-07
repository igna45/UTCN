library IEEE; 
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.ALL;
use ieee.std_logic_arith.all;

entity PmodOLEDCtrl is
    Port ( 
        CLK     : in  STD_LOGIC;
        RST     : in  STD_LOGIC;
        
        CS      : out STD_LOGIC;
        SDIN    : out STD_LOGIC;
        SCLK    : out STD_LOGIC;
        DC      : out STD_LOGIC;
        RES     : out STD_LOGIC;
        VBAT    : out STD_LOGIC;
        VDD     : out STD_LOGIC);
end PmodOLEDCtrl;

architecture Behavioral of PmodOLEDCtrl is

    component OledInit is
        Port ( CLK     : in  STD_LOGIC;
               RST     : in  STD_LOGIC;
               EN      : in  STD_LOGIC;
               CS      : out STD_LOGIC;
               SDO     : out STD_LOGIC;
               SCLK    : out STD_LOGIC;
               DC      : out STD_LOGIC;
               RES     : out STD_LOGIC;
               VBAT    : out STD_LOGIC;
               VDD     : out STD_LOGIC;
               FIN     : out STD_LOGIC);
    end component;

    component DisplayH is
        Port ( CLK     : in  STD_LOGIC;
               RST     : in  STD_LOGIC;
               EN      : in  STD_LOGIC;
               CS      : out STD_LOGIC;
               SDO     : out STD_LOGIC;
               SCLK    : out STD_LOGIC;
               DC      : out STD_LOGIC;
               FIN     : out STD_LOGIC);
    end component;

    type states is (Idle, OledInitialize, OledExample, DisplayHState, Done);

    signal current_state    : states := Idle;

    signal init_en          : STD_LOGIC := '0';
    signal init_done        : STD_LOGIC;
    signal init_cs          : STD_LOGIC;
    signal init_sdo         : STD_LOGIC;
    signal init_sclk        : STD_LOGIC;
    signal init_dc          : STD_LOGIC;

    signal example_en       : STD_LOGIC := '0';
    signal example_done     : STD_LOGIC;
    signal example_cs       : STD_LOGIC;
    signal example_sdo      : STD_LOGIC;
    signal example_sclk     : STD_LOGIC;
    signal example_dc       : STD_LOGIC;

    signal displayH_en      : STD_LOGIC := '0';
    signal displayH_done    : STD_LOGIC;
    signal displayH_cs      : STD_LOGIC;
    signal displayH_sdo     : STD_LOGIC;
    signal displayH_sclk    : STD_LOGIC;
    signal displayH_dc      : STD_LOGIC;

begin

    Init: OledInit port map(
        CLK => CLK, RST => RST, EN => init_en, 
        CS => init_cs, SDO => init_sdo, SCLK => init_sclk, 
        DC => init_dc, RES => RES, VBAT => VBAT, VDD => VDD, 
        FIN => init_done
    );
    
    DisplayHModule: DisplayH port map(
        CLK => CLK, RST => RST, EN => displayH_en, 
        CS => displayH_cs, SDO => displayH_sdo, SCLK => displayH_sclk, 
        DC => displayH_dc, FIN => displayH_done
    );

    -- MUXes to control which block is active and routing their outputs
    CS <= init_cs when (current_state = OledInitialize) else
         example_cs when (current_state = OledExample) else
         displayH_cs when (current_state = DisplayHState) else
         '1';

    SDIN <= init_sdo when (current_state = OledInitialize) else
           example_sdo when (current_state = OledExample) else
           displayH_sdo when (current_state = DisplayHState) else
           '0';

    SCLK <= init_sclk when (current_state = OledInitialize) else
           example_sclk when (current_state = OledExample) else
           displayH_sclk when (current_state = DisplayHState) else
           '0';

    DC <= init_dc when (current_state = OledInitialize) else
         example_dc when (current_state = OledExample) else
         displayH_dc when (current_state = DisplayHState) else
         '0';

    -- State machine process
    process(CLK)
    begin
        if rising_edge(CLK) then
            if RST = '1' then
                current_state <= Idle;
            else
                case current_state is
                    when Idle =>
                        current_state <= OledInitialize;
                    when OledInitialize =>
                        if init_done = '1' then
                            current_state <= OledExample;
                        end if;
                    when OledExample =>
                        if example_done = '1' then
                            current_state <= DisplayHState;
                        end if;
                    when DisplayHState =>
                        displayH_en <= '1';
                        if displayH_done = '1' then
                            current_state <= Done;
                        end if;
                    when Done =>
                        -- Remain in this state or add additional logic as needed
                    when others =>
                        current_state <= Idle;
                end case;
            end if;
        end if;
    end process;
    
end Behavioral;
