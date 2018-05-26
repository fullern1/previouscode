-- part3a.vhdl   VHDL '93 version using entities from WORK library
--              basic five stage pipeline of MIPS architecture
--              The 411 course pipeline has the same five stages
--              IF Instruction Fetch includes PC and instruction memory
--              ID Instruction Decode and registers
--              EX Execution including the ALU Arithmetic Logic Unit
--              MEM data Memory
--              WB Write Back into registers
--
--              The signal naming convention uses the stage as a prefix
--              WORK library needs entities and architectures for
--              add32  and  bshift and pmul8 and divcas16 .
--
-- This self contained VHDL file defines:
--     a package declaration and body that defines functions and memory
--     a 32 bit and a 5 bit register entity with clock and clear inputs
--     an instruction memory entity and behavioral architecture
--     a data memory entity and behavioral architecture
--     a general register entity and behavioral architecture
--     multiplexer entities and behavioral architectures
--     equal comparator entities and circuit architectures
--     an incomplete ALU entity and schematic architecture

--     a top level entity, part3a, test bench
--     the architecture, schematic layout of the top level entity
--     the signals for interconnecting the entities
--     a clock generator process
--     the entities connected with signals (port maps)
--     a memory read process that reads "part3a.abs"
--     a print process that shows the registers in the pipeline each clock

library IEEE;
use IEEE.std_logic_1164.all;

package util_pkg is
  function to_integer(sig : std_logic_vector) return integer;

  -- main memory, a process reads a file to load memory
  subtype word is std_logic_vector(31 downto 0);
  type mem_array is array(integer range <>) of word;
  shared variable memory: mem_array(0 to 4095);  -- max 12 bit addresses

  -- general register memory
  type reg_mem_type is array (natural range <>) of word;
  shared variable reg_mem : reg_mem_type(0 to 31) := (others =>(others =>'0'));
end package util_pkg;

package body util_pkg is
  function to_integer(sig : std_logic_vector) return integer is
    variable num : integer := 0;  -- descending sig as integer
  begin
    for i in sig'range loop
      if sig(i)='1' then
        num := num*2+1;
      else
        num := num*2;
      end if;
    end loop;  -- i
    return num;
  end function to_integer;
end package body util_pkg;



library IEEE;
use IEEE.std_logic_1164.all;

entity register_32 is
  port(clk    : in  std_logic;
       clear  : in  std_logic;
       input  : in  std_logic_vector (31 downto 0);
       output : out std_logic_vector (31 downto 0) );
end entity register_32;

architecture behavior of register_32 is
begin  -- behavior
  reg_32: process(clk, clear)
          begin
            if clear='1' then  -- only once
              output <= (others=>'0');
            elsif clk'event and clk='1' then
              output <= input after 250 ps;
            end if;
          end process reg_32;
end architecture behavior;  -- of register_32

library IEEE;
use IEEE.std_logic_1164.all;

entity register_5 is
  port(clk    : in  std_logic;
       clear  : in  std_logic;
       input  : in  std_logic_vector (4 downto 0);
       output : out std_logic_vector (4 downto 0) );
end entity register_5;

architecture behavior of register_5 is
begin  -- behavior
  reg_5: process(clk, clear)
         begin
           if clear='1' then  -- only once
             output <= (others=>'0');
           elsif clk'event and clk='1' then
             output <= input after 250 ps;
           end if;
         end process reg_5;
end architecture behavior;  -- of register_5


library IEEE;
use IEEE.std_logic_1164.all;
use WORK.util_pkg.all;
use STD.textio.all;
use IEEE.std_logic_textio.all;

entity instruction_memory is
  port(clk   : in  std_logic;
	   clear : in  std_logic;
       addr  : in  std_logic_vector (31 downto 0);
       inst  : out std_logic_vector (31 downto 0);
	   miss  : out std_logic);
end entity instruction_memory;

architecture behavior of instruction_memory is
	subtype block_type is std_logic_vector(154 downto 0);
	type cache_type is array (0 to 3) of block_type;
	signal cache : cache_type := (others=>(others=>'0'));
	signal local_miss : std_logic := '0';
	-- now we have a cache memory initialized to zero
begin  -- behavior
  inst_mem: process(addr, clear, local_miss) 
              variable word_addr : natural;  -- byte addr/4
			  variable quad_word_address : natural;  -- for memory fetch
              variable cblock : block_type;-- the shaded block in the cache
              variable index : natural;   -- index into cache to get a block
              variable word : natural;    -- select a word
              variable my_line : line;    -- for debug printout
              alias tag   : std_logic_vector(25 downto 0) is cblock(153 downto 128);
              alias w0    : std_logic_vector(31 downto 0) is cblock(127 downto 96);
			  alias w1    : std_logic_vector(31 downto 0) is cblock(95 downto 64);
			  alias w2    : std_logic_vector(31 downto 0) is cblock(63 downto 32);
			  alias w3    : std_logic_vector(31 downto 0) is cblock(31 downto 0);
              alias valid : std_logic is cblock(154); -- other alias allowed
            begin
              if clear='1' then  -- total machine clear  
			    miss <= '0';
                inst <= x"00000000";
			  end if;
              if clear='0' then -- normal operation
                word_addr := to_integer(addr(13 downto 2)); -- crop to 12 bits
                inst <= memory(word_addr) after 250 ps;
				
				index := to_integer(addr(5 downto 4));
                word  := to_integer(addr(3 downto 2));
				cblock := cache(index);  -- has valid (154), tag (153 downto 128)
                                       -- W0 (127 downto 96), W1(95 downto 64)
                                       -- W2(63 downto 32), W3 (31 downto 0)
                                       -- cblock is the shaded block in handout

				if (valid = '1') and (tag = addr(31 downto 6)) then -- hit
					miss <= '0';
				-- ... do hit	    
				else -- miss

					-- ... do miss, get 4 words from memory, set tag and valid
					--...
					quad_word_address := to_integer(addr(13 downto 4));
					w0 := memory(quad_word_address*4+0);
					w1 := memory(quad_word_address*4+1);
					w2 := memory(quad_word_address*4+2);
					w3 := memory(quad_word_address*4+3);
					tag:= addr(31 downto 6);
					valid:= '1';-- ...
                                       -- fill in cblock with new words, then
					cache(index) <= cblock after 30 ns; -- 3 clock delay
					miss <= '1', '0' after 30 ns;       -- miss is '1' for 30 ns
					local_miss <= '1', '0' after 30 ns; -- to get process to run 
					-- this "miss" signal gets ored into part2b "stall" signal
					--...
					-- the part3a.chk file has 'inst' set to zero while 'miss' is 1
					-- not required but cleans up the "diff"
				end if;
			  end if; -- clear = '0'
            end process inst_mem;
			  
end architecture behavior;  -- of instruction_memory


library IEEE;
use IEEE.std_logic_1164.all;
use WORK.util_pkg.all;

entity data_memory is
  port(address      : in  std_logic_vector (31 downto 0);
       write_data   : in  std_logic_vector (31 downto 0);
       read_enable  : in  std_logic;  -- from address
       write_enable : in  std_logic;  -- rising clock and enable
       write_clk    : in  std_logic;  -- required to write
       read_data    : out std_logic_vector (31 downto 0));
end entity data_memory;

architecture behavior of data_memory is
begin  -- behavior
  data_mem: process(address, write_clk)
              variable word_addr : natural;  -- byte addr/4
            begin
              if write_enable='1' and write_clk='1' then
                word_addr := to_integer(address(13 downto 2));  -- 12 bits
                memory(word_addr) := write_data;  -- write main memory
                read_data <= write_data;  -- just something to output
              elsif read_enable='1' then
                word_addr := to_integer(address(13 downto 2));  -- 12 bits
                read_data <= memory(word_addr) after 250 ps;  -- read memory
              else
                read_data <= x"00000000";  -- just to clean up printout
              end if;
            end process data_mem;
end architecture behavior;  -- of data_memory


library IEEE;
use IEEE.std_logic_1164.all;
use WORK.util_pkg.all;

entity registers is
  port(read_reg_1   : in  std_logic_vector (4 downto 0); -- address
       read_reg_2   : in  std_logic_vector (4 downto 0); -- address
       write_reg    : in  std_logic_vector (4 downto 0); -- address
       write_data   : in  std_logic_vector (31 downto 0);
       write_enable : in  std_logic;  -- rising clock and enable
       write_clk    : in  std_logic;  -- required to write
       read_data_1  : out std_logic_vector (31 downto 0);
       read_data_2  : out std_logic_vector (31 downto 0));
end entity registers;

architecture behavior of registers is
begin  -- behavior
  reg: process(read_reg_1, read_reg_2, write_clk)
         variable reg_addr : natural;
       begin
         if write_enable='1' and write_clk'active and write_clk='1' then
           reg_addr := to_integer(write_reg);
           if reg_addr/=0 then           -- can not change register zero
             reg_mem(reg_addr) := write_data;
           end if;
         end if;
         read_data_1 <= reg_mem(to_integer(read_reg_1));
         read_data_2 <= reg_mem(to_integer(read_reg_2));
         -- signals updated after process exits
       end process reg;
end architecture behavior;  -- of registers

library IEEE;
use IEEE.std_logic_1164.all;

entity mux_32 is
  port(in0    : in  std_logic_vector (31 downto 0);
       in1    : in  std_logic_vector (31 downto 0);
       ctl    : in  std_logic;
       result : out std_logic_vector (31 downto 0));
end entity mux_32;

architecture behavior of mux_32 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ctl='1' else in0 after 250 ps;
end architecture behavior;  -- of mux_32

library IEEE;
use IEEE.std_logic_1164.all;
entity mux32_3 is
  port(in0    : in  std_logic_vector (31 downto 0);
       in1    : in  std_logic_vector (31 downto 0);
       in2    : in  std_logic_vector (31 downto 0);
       ct1    : in  std_logic;          -- pass in1(has priority)
       ct2    : in  std_logic;          -- pass in2
       result : out std_logic_vector (31 downto 0));
end entity mux32_3;

architecture behavior of mux32_3 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ct1='1' else in2 when ct2='1' else in0 after 50 ps;
end architecture behavior;  -- of mux32_3

library IEEE;
use IEEE.std_logic_1164.all;

entity mux32_6 is
  port(in0    : in  std_logic_vector (31 downto 0);
       in1    : in  std_logic_vector (31 downto 0);
       in2    : in  std_logic_vector (31 downto 0);
       in3    : in  std_logic_vector (31 downto 0);
       in4    : in  std_logic_vector (31 downto 0);
       in5    : in  std_logic_vector (31 downto 0);
       ct1   : in  std_logic;
       ct2   : in  std_logic;
       ct3   : in  std_logic;
       ct4   : in  std_logic;
       ct5   : in  std_logic;
       result : out std_logic_vector (31 downto 0));
end entity mux32_6;

architecture behavior of mux32_6 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ct1='1' else in2 when ct2='1' else
            in3 when ct3='1' else in4 when ct4='1' else
            in5 when ct5='1' else in0 after 100 ps;
end architecture behavior;  -- of mux32_6

library IEEE;
use IEEE.std_logic_1164.all;

entity mux_5 is
  port(in0    : in  std_logic_vector (4 downto 0);
       in1    : in  std_logic_vector (4 downto 0);
       ctl    : in  std_logic;
       result : out std_logic_vector (4 downto 0));
end entity mux_5;

architecture behavior of mux_5 is 
begin  -- behavior -- no process needed with concurrent statements
  result <= in1 when ctl='1' else in0 after 250 ps;
end architecture behavior;  -- of mux_5

library IEEE;
use IEEE.std_logic_1164.all;

entity equal32 is --  a 32-bit compare
  port(inst  : in  std_logic_vector(31 downto 0);
       test  : in  std_logic_vector(31 downto 0);
       equal : out std_logic);
end entity equal32;

architecture circuits of equal32 is
  signal temp : std_logic_vector(0 to 32) := (others=>'1');
begin  -- circuits
  t1: for I in 0 to 31 generate
        temp(I+1) <= (inst(I) xnor test(I)) and temp(I);
      end generate t1;
  equal <= temp(32);
end architecture circuits;  -- of equal32

library IEEE;
use IEEE.std_logic_1164.all;

entity equal6 is -- basically a 6-bit op code compare
  port(inst  : in  std_logic_vector(5 downto 0);
       test  : in  std_logic_vector(5 downto 0);
       equal : out std_logic);
end entity equal6;

architecture circuits of equal6 is
  signal temp : std_logic_vector(0 to 6) := (others=>'1');
begin  -- circuits
  t1: for I in 0 to 5 generate
        temp(I+1) <= (inst(I) xnor test(I)) and temp(I);
      end generate t1;
  equal <= temp(6);
end architecture circuits;  -- of equal6

library IEEE;
use IEEE.std_logic_1164.all;

entity equal5 is -- basically a 5-bit register number compare
  port(inst  : in  std_logic_vector(4 downto 0);
       test  : in  std_logic_vector(4 downto 0);
       equal : out std_logic);
end entity equal5;

architecture circuits of equal5 is
  signal temp : std_logic_vector(0 to 5) := (others=>'1');
begin  -- circuits
  t1: for I in 0 to 4 generate
        temp(I+1) <= (inst(I) xnor test(I)) and temp(I);
      end generate t1;
  equal <= temp(5);
end architecture circuits;  -- of equal5


library IEEE;
use IEEE.std_logic_1164.all;

entity alu_32 is
  port(inA    : in  std_logic_vector (31 downto 0);
       inB    : in  std_logic_vector (31 downto 0);
       inst   : in  std_logic_vector (31 downto 0);
       result : out std_logic_vector (31 downto 0));
end entity alu_32;


architecture schematic of alu_32 is 
  signal cin     : std_logic := '0';
  signal cout    : std_logic;
  signal S_sel     : std_logic;
  signal sllop     : std_logic;
  signal sllop_and : std_logic;
  signal srlop     : std_logic;
  signal srlop_and : std_logic;
  signal RRop      : std_logic;
  signal orop      : std_logic;
  signal orop_and  : std_logic;
  signal andop     : std_logic;
  signal andop_and : std_logic;
  signal mulop     : std_logic;
  signal mulop_and : std_logic;
  signal divop     : std_logic;
  signal divop_and : std_logic;
  signal subop     : std_logic;
  signal subop_and : std_logic;
  signal cmplop    : std_logic;
  signal cmplop_and: std_logic;
  signal subop_or_cmplop  : std_logic;
  signal mulresult : std_logic_vector (31 downto 0);
  signal divresult : std_logic_vector (31 downto 0);
  signal divrem    : std_logic_vector (31 downto 0);
  signal aresult   : std_logic_vector (31 downto 0);
  signal orresult  : std_logic_vector (31 downto 0);
  signal andresult : std_logic_vector (31 downto 0);
  signal bresult   : std_logic_vector (31 downto 0);
  signal amuxres   : std_logic_vector (31 downto 0);
  signal notinB    : std_logic_vector (31 downto 0);
  -- add many more signals needed in ALU
  
begin  -- schematic
  --
  --   ADD TO THIS SECTION FOR PROJECT PART 1   
  --   (add the signals you need above "begin"
  --
  ORR : entity WORK.equal6 port map(inst(31 downto 26), "000000", RRop);
  Oor: entity WORK.equal6 port map(inst(5 downto 0), "001101", orop);
  Oand: entity WORK.equal6 port map(inst(5 downto 0), "001111", andop);
  Omul: entity WORK.equal6 port map(inst(5 downto 0), "011011", mulop);
  Odiv: entity WORK.equal6 port map(inst(5 downto 0), "011000", divop);
  Osub: entity WORK.equal6 port map(inst(5 downto 0), "100010", subop);
  Osrl: entity WORK.equal6 port map(inst(5 downto 0), "000011", srlop);
  Osll: entity WORK.equal6 port map(inst(5 downto 0), "000010", sllop);
  Ocmpl: entity WORK.equal6 port map(inst(5 downto 0), "001011", cmplop);
  
  orop_and <= orop and RRop;
  mulop_and <= mulop and RRop;
  divop_and <= divop and RRop;
  andop_and <= andop and RRop;
  sllop_and <= sllop and RRop;
  srlop_and <= srlop and RRop;
  subop_and <= subop and RRop;
  cmplop_and<= cmplop and RRop;
  subop_or_cmplop <= subop_and or cmplop_and;
  S_sel <= sllop_and or srlop_and;
  orresult <= inA or inB;
  andresult <= inA and inB;
  
  bsh: entity WORK.bshift port map(left => sllop_and,
                                   logical => '1',
                                   shift => inst(10 downto 6),
                                   input => inB,
                                   output => bresult);
  
  notinB <= not inB;
  Amux: entity WORK.mux_32 port map(in0 => inB,
                                    in1 => notinB,  
                                    ctl => subop_or_cmplop,
                                    result => amuxres);

  subt: entity WORK.add32 port map(a => inA,
                                   b => amuxres,
                                   cin => subop_and,
                                   sum => aresult,
                                   cout => open);
                                    
  Mul8: entity WORK.pmul8 port map(a => inA(7 downto 0),
                                   b => inB(7 downto 0),
                                   p => mulresult(15 downto 0));

  Div16: entity WORK.divcas16 port map(dividend => inA,
                                       divisor => inB(15 downto 0),
                                       quotient => divresult(15 downto 0),
                                       remainder => divrem(15 downto 0));

  Omux: entity WORK.mux32_6 port map(in0=>aresult,
                                     in1=>orresult,
                                     in2=>andresult,
                                     in3=>mulresult,
                                     in4=>divresult,
                                     in5=>bresult,
                                     ct1=>orop_and,
                                     ct2=>andop_and,
                                     ct3=>mulop_and,
                                     ct4=>divop_and,
                                     ct5=>S_sel,
                                     result=>result);
  
end architecture schematic;  -- of alu_32


entity part3a is  -- test bench
end part3a;

library STD;
use STD.textio.all;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_textio.all;
use WORK.util_pkg.all;

architecture schematic of part3a is -- top level connection of entities
  
  -- signals used in top level architecture (the interconnections)
  
  subtype word_32 is std_logic_vector(31 downto 0);  -- data and inst
  subtype word_6 is std_logic_vector(5 downto 0);    -- op codes
  subtype word_5 is std_logic_vector(4 downto 0);    -- register numbers
  
  signal zero_32 : word_32 := (others=>'0');     -- 32 bits of zero
  signal zero    : std_logic := '0';             -- one bit zero
  signal four_32 : word_32 := x"00000004";       -- four

  -- from  cs411_opcodes.txt 
  signal lwop    : word_6 := "100011";     -- lw op code
  signal swop    : word_6 := "101011";     -- sw op code
  signal RRop    : word_6 := "000000";     -- RR op code
  signal addiop  : word_6 := "001100";     -- addi op code
  signal lwimop  : word_6 := "001111";     -- lwim op code
  signal jumpop  : word_6 := "000010";
  signal beqop   : word_6 := "011011";
  signal jump    : std_logic;
  signal sw      : std_logic;
  signal beq     : std_logic;
  signal jbs     : std_logic;
  
  -- signals for part3a
  signal sclk       : std_logic;
  signal stall      : std_logic;
  signal stall_lw   : std_logic;
  signal stall_lwlw : std_logic;
  signal stall_mem  : std_logic;
  signal stall_beq  : std_logic;
  signal slw1, slw2, slw3, slw3a, slw3b, slw4, slw5, slw6 : std_logic;
  signal slwl1, slwl2, slwl3, slwl3a, slwl3b, slwl4 : std_logic;
  signal smem1, smem2, smem3, smem4, smem4a, smem4b : std_logic;
  signal sbeq1, sbeq2, sbeq3, sbeq3a, sbeq3b : std_logic;
  signal ID_2b_mux : word_32;
  
  signal cache_miss : std_logic;
  
  signal clear   : std_logic := '1';       -- one shot clear
  signal clk     : std_logic := '1';       -- master clock
  signal clk_bar : std_logic := '0';       -- complement of master clock
  signal counter : integer := 0;           -- master clock counter,raising edge
  
  signal PC_next        : word_32;            -- next value of PC 
  signal PC             : word_32;            -- Program Counter
  signal inst           : word_32;            -- instruction fetched

  signal PCP            : word_32;
  signal PC_add         : word_32;
  signal PCP_add        : word_32;
  
  signal ID_IR          : word_32;            -- ID Instruction Register
  signal ID_read_data_1 : word_32;            -- ID Register read data 1
  signal ID_read_data_2 : word_32;            -- ID Register read data 2
  signal ID_sign_ext    : word_32;            -- ID sign extension
  signal RegDst         : std_logic := '0';   -- ID register destination ctl
  signal ID_rd          : word_5;             -- ID register destination
  signal old_ID_rd      : word_5;
  alias  ID_addr        : std_logic_vector(15 downto 0) is ID_IR(15 downto 0);
  
  signal EX_IR          : word_32;            -- EX Instruction Register
  signal EX_A           : word_32;            -- EX data A
  signal EX_B           : word_32;            -- EX data B
  signal EX_C           : word_32;            -- EX data C
  signal EX_rd          : word_5;             -- EX register destination
  signal EX_aluB        : word_32;            -- EX into ALU B
  signal ALUSrc         : std_logic := '1';   -- EX ALU B side source control
  signal ALUSrcn        : std_logic := '0';   -- EX
  signal EX_result      : word_32;            -- EX ALU output

  signal EX_AA          : word_32;
  signal EX_BB          : word_32;
  signal AFMA, AFMA1, AFMA2, AFMA3 : std_logic;
  signal BFMA, BFMA1, BFMA2, BFMA3 : std_logic;
  signal AFWR, AFWR1, AFWR2        : std_logic;
  signal BFWR, BFWR1, BFWR2        : std_logic;
  signal shifted2       : word_32;
  signal jump_addr      : word_32;
  signal fwone, fwone1, fwone2, fwone3 : std_logic;
  signal fwtwo, fwtwo1, fwtwo2, fwtwo3 : std_logic;
  
  signal MEM_IR         : word_32;            -- mem inst register
  signal MEM_addr       : word_32;            -- mem address
  signal MEM_data       : word_32;            -- mem write data
  signal MEM_read_data  : word_32;            -- mem read data
  signal MEM_rd         : word_5;             -- mem register destination
  signal MEMRead        : std_logic := '1';   -- mem enable read
  signal MEMWrite       : std_logic := '0';   -- mem enable write
  
  signal WB_IR          : word_32;            -- wb instruction register
  signal WB_read        : word_32;            -- wb read data
  signal WB_pass        : word_32;            -- wb pass data
  signal WB_rd          : word_5;             -- wb register destination
  signal WB_rd_zero     : std_logic;          -- wb_rd is zero, no value
  signal MemtoReg       : std_logic := '1';   -- wb mux control
  signal WB_result      : word_32;            -- wb mux output
  signal WB_write_enb   : std_logic := '1';   -- wb enable register write
  signal WB_lwop        : std_logic;          -- have a lw in wb stage
  signal WB_lwimop      : std_logic;          -- have a lwim in wb stage
  signal WB_RRop        : std_logic;
  signal WB_addiop      : std_logic;

  signal eq_beq_res     : std_logic;
  signal d1mux          : word_32;
  signal d2mux          : word_32;
  signal eqresult       : std_logic;
  
begin  -- schematic of part3a, top level architecture and test bench
               
  clock_gen: process(clk, clear)  -- clock generator and one shot clear signal
             begin
               if clear='1' then -- happens only once
                 clear <= '0' after 200 ps;
               elsif clear='0' then     -- avoid time zero glitch
                 clk <= not clk after 5 ns;  -- 10 ns period
               end if;
             end process clock_gen;

             clk_bar <= not clk;               -- for split phase registers
			 
-- if, instruction fetch pipeline stage
  PC_reg:    entity WORK.register_32 port map(sclk, clear, PC_next, PC);
  PC_incr:   entity WORK.add32 port map(PC, four_32, zero, PC_add, open);
  inst_mem:  entity WORK.instruction_memory port map(sclk, clear, PC, inst, cache_miss);

-- adding to this part
  PCP_reg:   entity WORK.register_32 port map(sclk, clear, PC_add, PCP);
  jump_addr <= PCP(31 downto 28) & ID_IR(25 downto 0) & "00";
  shifted2 <= ID_sign_ext(29 downto 0) & "00";
             
  PC_adder:  entity WORK.add32 port map(PCP, shifted2, zero, PCP_add, open);

  PC_reg_mux:entity WORK.mux32_3 port map(PC_add,
                                          jump_addr,
                                          PCP_add,
                                          jump, 
                                          eq_beq_res,
                                          PC_next);

-- part3a work 
  -- stall_lw
  sl1:  entity WORK.equal6 port map(EX_IR(31 downto 26), lwop, slw1);
  sl2:  entity WORK.equal5 port map(EX_rd, "00000", slw2);
  sl3a: entity WORK.equal5 port map(ID_IR(25 downto 21), EX_rd, slw3a);
  sl3b: entity WORK.equal5 port map(ID_IR(20 downto 16), EX_rd, slw3b);
  sl4:  entity WORK.equal6 port map(ID_IR(31 downto 26), lwop, slw4);
  sl5:  entity WORK.equal6 port map(ID_IR(31 downto 26), addiop, slw5);
  sl6:  entity WORK.equal6 port map(ID_IR(31 downto 26), jumpop, slw6);
  sl3:  slw3 <= slw3a or slw3b;
  sl7:  stall_lw <= slw1 and not slw2 and slw3 and not slw4 and not slw5 and not slw6;
  
  -- stall_lwlw
  sll1:  entity WORK.equal6 port map(EX_IR(31 downto 26), lwop, slwl1);
  sll2:  entity WORK.equal5 port map(EX_rd, "00000", slwl2);
  sll3a: entity WORK.equal6 port map(ID_IR(31 downto 26), lwop, slwl3a);
  sll3b: entity WORK.equal6 port map(ID_IR(31 downto 26), addiop, slwl3b);
  sll4:  entity WORK.equal5 port map(ID_IR(25 downto 21), EX_rd, slwl4);
  sll3: slwl3 <= slwl3a or slwl3b;
  sll5: stall_lwlw <= slwl1 and not slwl2 and slwl3 and slwl4;
  
  -- stall_mem
  sm1:  entity WORK.equal6 port map (ID_IR(31 downto 26), beqop, smem1);
  sm2:  entity WORK.equal5 port map (MEM_rd, "00000", smem2);
  sm3:  entity WORK.equal6 port map (MEM_IR(31 downto 26), lwop, smem3);
  sm4a: entity WORK.equal5 port map (ID_IR(25 downto 21), MEM_rd, smem4a);
  sm4b: entity WORK.equal5 port map (ID_IR(20 downto 16), MEM_rd, smem4b);
  sm4:  smem4 <= smem4a or smem4b;
  sm5:  stall_mem <= smem1 and not smem2 and smem3 and smem4;
  
  -- stall_beq
  sb1:  entity WORK.equal6 port map (ID_IR(31 downto 26), beqop, sbeq1);
  sb2:  entity WORK.equal5 port map (EX_rd, "00000", sbeq2);
  sb3a: entity WORK.equal5 port map (ID_IR(25 downto 21), EX_rd, sbeq3a);
  sb3b: entity WORK.equal5 port map (ID_IR(20 downto 16), EX_rd, sbeq3b);
  sb3:  sbeq3 <= sbeq3a or sbeq3b;
  sb4:  stall_beq <= sbeq1 and not sbeq2 and sbeq3;
  
  stall <= stall_lw or stall_lwlw or stall_mem or stall_beq or cache_miss;
  sclk <= stall or clk;
  
-- id, instruction decode and register stack pipeline stage
  ID_IR_reg: entity WORK.register_32 port map(sclk, clear, inst, ID_IR);
  ID_regs:   entity WORK.registers port map(
                                read_reg_1   => ID_IR(25 downto 21),
                                read_reg_2   => ID_IR(20 downto 16),
                                write_reg    => WB_rd,
                                write_data   => WB_result,
                                write_enable => WB_write_enb,
                                write_clk    => clk_bar,
                                read_data_1  => ID_read_data_1,
                                read_data_2  => ID_read_data_2);

  RegDstC  : entity WORK.equal6 port map(ID_IR(31 downto 26), RRop, RegDst);
    -- regdst <=   must compute 
             
  old_ID_mux_rd: entity WORK.mux_5 port map(in0    => ID_IR(20 downto 16),
                                        in1    => ID_IR(15 downto 11),
                                        ctl    => RegDst,
                                        result => old_ID_rd);
             ID_sign_ext(15 downto 0) <= ID_addr;  -- just wiring
             ID_sign_ext(31 downto 16) <= (others => ID_IR(15));

  jbs <= jump or beq or sw or stall;
  ID_mux_rd: entity WORK.mux_5 port map(in0 => old_ID_rd,
                                        in1 => "00000",
                                        ctl => jbs,
                                        result => ID_rd);

  eqf11    : entity WORK.equal5 port map(ID_IR(25 downto 21), MEM_RD, fwone1);
  eqf12    : entity WORK.equal5 port map(MEM_RD, "00000", fwone2);
  eqf13    : entity WORK.equal6 port map(MEM_IR(31 downto 26), "100011",
                                         fwone3);
  fwone <= fwone1 and not fwone2 and not fwone3;

  eqf21    : entity WORK.equal5 port map(ID_IR(20 downto 16), MEM_RD, fwtwo1);
  eqf22    : entity WORK.equal5 port map(MEM_RD, "00000", fwtwo2);
  eqf23    : entity WORK.equal6 port map(MEM_IR(31 downto 26), "100011",
                                         fwtwo3);
  fwtwo <= fwtwo1 and not fwtwo2 and not fwtwo3;
             
  d1_mux   : entity WORK.mux_32 port map(ID_read_data_1,
                                        MEM_addr,
                                        fwone,
                                        d1mux);

  d2_mux   : entity WORK.mux_32 port map(ID_read_data_2,
                                        MEM_addr,
                                        fwtwo,
                                        d2mux);

  eq_op    : entity WORK.equal32 port map(d1mux,
                                          d2mux,
                                          eqresult);

  eq_beq_res <= eqresult and beq;

  eq6jjump : entity WORK.equal6 port map(ID_IR(31 downto 26),
                                         jumpop,
                                         jump);
  eq6beq   : entity WORK.equal6 port map(ID_IR(31 downto 26),
                                         beqop,
                                         beq);
  eq6sw    : entity WORK.equal6 port map(ID_IR(31 downto 26),
                                         swop,
                                         sw);

-- add mux_32 for part3a
  p2bmux: entity WORK.mux_32 port map (ID_IR,
                                       "00000000000000000000000000000000",
									   stall,
							           ID_2b_mux);
										 
-- ex, execute pipeline stage
  EX_IR_reg: entity WORK.register_32 port map(clk, clear, ID_2b_mux, EX_IR);
  EX_A_reg : entity WORK.register_32 port map(clk, clear, ID_read_data_1,EX_A);
  EX_B_reg : entity WORK.register_32 port map(clk, clear, ID_read_data_2,EX_B);
  EX_C_reg : entity WORK.register_32 port map(clk, clear, ID_sign_ext, EX_C);
  EX_rd_reg: entity WORK.register_5  port map(clk, clear, ID_rd, EX_rd);

  eq1      : entity WORK.equal5 port map(EX_IR(25 downto 21), MEM_RD, AFMA1);
  eq2      : entity WORK.equal5 port map(MEM_RD, "00000", AFMA2);
  eq3      : entity WORK.equal6 port map(MEM_IR(31 downto 26), "100011",
                                         AFMA3);
  AFMA <= AFMA1 and not AFMA2 and not AFMA3;

  eq4      : entity WORK.equal5 port map(EX_IR(25 downto 21), WB_RD, AFWR1);
  eq5      : entity WORK.equal5 port map(WB_RD, "00000", AFWR2);

  AFWR <= AFWR1 and not AFWR2;
             
  eq7      : entity WORK.equal5 port map(EX_IR(20 downto 16), MEM_RD, BFMA1);
  eq8      : entity WORK.equal5 port map(MEM_RD, "00000", BFMA2);
  eq9      : entity WORK.equal6 port map(MEM_IR(31 downto 26), "100011",
                                         BFMA3);
  BFMA <= BFMA1 and not BFMA2 and not BFMA3;

  eq10     : entity WORK.equal5 port map(EX_IR(20 downto 16), WB_RD, BFWR1);
  eq11     : entity WORK.equal5 port map(WB_RD, "00000", BFWR2);

  BFWR <= BFWR1 and not BFWR2;
             
  EX_A_M   : entity WORK.mux32_3 port map(EX_A,
                                          MEM_addr,
                                          WB_result,
                                          AFMA,
                                          AFWR,
                                          EX_AA);

  EX_B_M   : entity WORK.mux32_3 port map(EX_B,
                                          MEM_addr,
                                          WB_result,
                                          BFMA,
                                          BFWR,
                                          EX_BB);
             
           -- ALUSrc <=   must compute  
  ALUSrcC  : entity WORK.equal6 port map(EX_IR(31 downto 26),
                                         RRop,
                                         ALUSrcn);
  ALUSrc <= not ALUSrcn;
             
  EX_mux1  : entity WORK.mux_32 port map(in0    => EX_BB,
                                         in1    => EX_C,
                                         ctl    => ALUSrc,
                                         result => EX_aluB );

  ALU      : entity WORK.alu_32 port map(inA   => EX_AA,
                                         inB   => EX_aluB,
                                         inst  => EX_IR,
                                         result=> EX_result);

-- MEM Data Memory pipeline stage
  MEM_IR_reg  : entity WORK.register_32 port map(clk, clear, EX_IR, MEM_IR);
  MEM_addr_reg: entity WORK.register_32 port map(clk, clear, EX_result,
                                                 MEM_addr);
  MEM_data_reg: entity WORK.register_32 port map(clk, clear, EX_BB, MEM_data);
  MEM_rd_reg  : entity WORK.register_5  port map(clk, clear, EX_rd, MEM_rd);

  MEM_lw      : entity WORK.equal6 port map(MEM_IR(31 downto 26), lwop,
                                            MEMRead);
             
     -- MEMWrite <=     must compute 
  MEM_sw      : entity WORK.equal6 port map(MEM_IR(31 downto 26),
                                            swop,
                                            MEMWrite);
             
  data_mem    : entity WORK.data_memory port map(address     => MEM_addr,
                                                 write_data  => MEM_data,
                                                 read_enable => MEMRead,
                                                 write_enable=> MEMWrite,
                                                 write_clk   => clk_bar,
                                                 read_data   => MEM_read_data);
             
-- WB, Write Back pipeline stage
  WB_IR_reg  : entity WORK.register_32 port map(clk, clear, MEM_IR, WB_IR);
  WB_read_reg: entity WORK.register_32 port map(clk, clear, MEM_read_data,
                                                WB_read);
  WB_pass_reg: entity WORK.register_32 port map(clk, clear, MEM_addr, WB_pass);
  WB_rd_reg  : entity WORK.register_5  port map(clk, clear, MEM_rd, WB_rd);
  wblwop     : entity WORK.equal6 port map(WB_IR(31 downto 26), lwop, WB_lwop);
  wblwimop   : entity WORK.equal6 port map(WB_IR(31 downto 26), lwimop, WB_lwimop);             
             MemtoReg <= WB_lwop;
  wbrrop     : entity WORK.equal6 port map(WB_IR(31 downto 26), RRop, WB_RRop);
  wbaddiop   : entity WORK.equal6 port map(WB_IR(31 downto 26), addiop, WB_addiop);
  compare_rd : entity WORK.equal5 port map(WB_rd, "00000", WB_rd_zero);
               WB_write_enb <= (not WB_rd_zero) and
                               (WB_lwop or WB_lwimop or
                                WB_RRop or WB_addiop);
                                  --  or WB_RRop or WB_addiop 

  WB_mux     : entity WORK.mux_32 port map(in0    => WB_pass,
                                           in1    => WB_read,
                                           ctl    => MemtoReg,
                                           result => WB_result );
    
  loadmem: process    -- read part3a.abs into shared memory array
             file my_input : TEXT open READ_MODE is "part3a.abs";  -- hex data
             variable good : boolean := true;
             variable my_line : LINE;
             variable my_input_line : LINE;
             variable loc : std_logic_vector(31 downto 0);  -- read from file
             variable val : std_logic_vector(31 downto 0);  -- read from file
             variable word_addr : natural;  -- byte addr/4
           begin
             write(my_line, string'
                   ("---PC--- --inst--  loadmem process input .abs file"));
             writeline(output, my_line);
             while good loop
               exit when endfile(my_input);
               readline(my_input, my_input_line);
               my_line := new string'(my_input_line.all);  -- for printing
               writeline(output, my_line); -- writing clears my_line
               hread(my_input_line, loc, good);
               exit when not good;
               hread(my_input_line, val, good);
               exit when not good;
               word_addr := to_integer(loc(13 downto 2)); -- crop to 12 bits
               memory(word_addr) := val;  -- write main memory
             end loop;
             write(my_line, string'("loadmem ends. memory loaded"));
             writeline(output, my_line);
             wait; -- run once. do not keep restarting process
           end process loadmem;
           
  printout:  process -- used to show pipeline, registers and memory
               variable my_line : LINE;   -- not part of working circuit
             begin
               wait for 9.5 ns;         -- just before rising clock
               write(my_line, string'("clock "));
               write(my_line, counter);
               write(my_line, string'("  inst="));
               hwrite(my_line, inst);
               write(my_line, string'("  PC   ="));
               hwrite(my_line, PC);
               write(my_line, string'(" PCnext="));
               hwrite(my_line, PC_next);
               writeline(output, my_line);
               write(my_line, string'("ID  stage  IR="));
               hwrite(my_line, ID_IR);
               if (WB_write_enb='1') and (WB_rd/="00000") then
                 write(my_line, string'("  write="));
                 hwrite(my_line, WB_result);
                 write(my_line, string'("  into ="));
                 hwrite(my_line, "000000000000000000000000000"&WB_rd);
               else
                 write(my_line, string'("                "));
                 write(my_line, string'("                "));
               end if;
               write(my_line, string'("                "));
               write(my_line, string'(" rd="));
               write(my_line, ID_rd);
               writeline(output, my_line);

               write(my_line, string'("EX  stage  IR="));
               hwrite(my_line, EX_IR);
               write(my_line, string'("  EX_A ="));
               hwrite(my_line, EX_A);
               write(my_line, string'("  EX_B ="));
               hwrite(my_line, EX_B);
               write(my_line, string'("  EX_C ="));
               hwrite(my_line, EX_C);
               write(my_line, string'(" rd="));
               write(my_line, EX_rd);
               writeline(output, my_line);
               write(my_line, string'("EX  stage"));
               write(my_line, string'("             "));
               write(my_line, string'("EX_aluB="));
               hwrite(my_line, EX_aluB);
               write(my_line, string'(" EX_res="));
               hwrite(my_line, EX_result);
               writeline(output, my_line);
               write(my_line, string'("MEM stage  IR="));
               hwrite(my_line, MEM_IR);
               write(my_line, string'("  addr ="));
               hwrite(my_line, MEM_addr);
               write(my_line, string'("  data ="));
               hwrite(my_line, MEM_data);
               if MEMread='1' then
                 write(my_line, string'("  read ="));
                 hwrite(my_line, MEM_read_data);
               elsif MEMWrite='1' then
                 write(my_line, string'("  wrote="));
                 hwrite(my_line, MEM_data);
               else
                 write(my_line, string'("                "));
               end if;
               write(my_line, string'(" rd="));
               write(my_line, MEM_rd);
               writeline(output, my_line);
               write(my_line, string'("WB  stage  IR="));
               hwrite(my_line, WB_IR);
               write(my_line, string'("  read ="));
               hwrite(my_line, WB_read);
               write(my_line, string'("  pass ="));
               hwrite(my_line, WB_pass);
               write(my_line, string'(" result="));
               hwrite(my_line, WB_result);
               write(my_line, string'(" rd="));
               write(my_line, WB_rd);
               writeline(output, my_line);
               write(my_line, string'("control RegDst="));
               write(my_line, RegDst);
               write(my_line, string'("  ALUSrc="));
               write(my_line, ALUSrc);
               write(my_line, string'("  MemtoReg="));
               write(my_line, MemtoReg);
               write(my_line, string'("  MEMRead="));
               write(my_line, MEMRead);
               write(my_line, string'("  MEMWrite="));
               write(my_line, MEMWrite);
               write(my_line, string'("  WB_write_enb="));
               write(my_line, WB_write_enb);
               writeline(output, my_line);

               -- registers
               write(my_line, string'("reg 0-7 "));
               for I in 0 to 7 loop
                 hwrite(my_line, reg_mem(I));
                 write(my_line, string'(" "));            
               end loop;  -- I
               writeline(output, my_line);
               write(my_line, string'("   8-15 "));
               for I in 8 to 15 loop
                 hwrite(my_line, reg_mem(I));
                 write(my_line, string'(" "));            
               end loop;  -- I
               writeline(output, my_line);
               write(my_line, string'("  16-23 "));
               for I in 16 to 23 loop
                 hwrite(my_line, reg_mem(I));
                 write(my_line, string'(" "));            
               end loop;  -- I
               writeline(output, my_line);
                 
               -- RAM memory
               write(my_line, string'("RAM 70- "));
               for I in 28 to 35 loop  -- word at hex 70 byte address
                 hwrite(my_line, memory(I));
                 write(my_line, string'(" "));
               end loop;
               writeline(output, my_line);
			   
               writeline(output, my_line);  -- blank line
               counter <= counter+1;
               wait for 0.5 ns;         -- rest of 10 ns clock period
             end process printout;

end architecture schematic; -- of part3a

