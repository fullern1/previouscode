-- tpmul8.vhdl   test pmul8.vhdl

library STD;
use STD.textio.all;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_textio.all;
use IEEE.std_logic_arith.all;

entity tpmul8 is                 -- test bench for pmul8.vhdl
end tpmul8;

architecture circuits of tpmul8 is
  signal a:    std_logic_vector(7 downto 0) := x"00";
                                      -- initial value of 8 bits of zero
  signal b:    std_logic_vector(7 downto 0) := x"FF";
                                      -- initial 8 bit hexadecimal value    
  signal prod:  std_logic_vector(15 downto 0);


  procedure my_printout(a:    std_logic_vector(7 downto 0);
                        b:    std_logic_vector(7 downto 0);
                        prod:  std_logic_vector(15 downto 0);
                        cntr: integer) is
    variable my_line : LINE;
  begin

    write(my_line, string'(" a="));
    hwrite(my_line, a);
    write(my_line, string'(", b="));
    hwrite(my_line, b);
    write(my_line, string'(", prod="));
    hwrite(my_line, prod);
    write(my_line, string'(", cntr="));
    write(my_line, cntr);
    write(my_line, string'(", at="));
    write(my_line, now);
    writeline(output, my_line);
  end my_printout;
  
begin  -- circuits of tpmul8
  mul: entity WORK.pmul8 port map(a, b, prod); -- parallel circuit
                                               -- your HW6
  
  driver: process                               -- serial code
            variable my_line : line;
            subtype word is std_logic_vector(7 downto 0);
            type vector16 is array(0 to 15) of word;
            variable ta : vector16 :=
              (x"00", x"FF", x"88", x"20",
               x"33", x"44", x"55", x"66",
               x"77", x"88", x"99", x"AA",
               x"BB", x"CC", x"DD", x"EE");
            variable tb : vector16 :=
              (x"FF", x"00", x"88", x"DD",
               x"0C", x"BB", x"AA", x"99",
               x"88", x"77", x"66", x"45",
               x"43", x"33", x"22", x"11");
          begin  -- process driver
            write(my_line, string'("Driver starting."));
            writeline(output, my_line);
            
            for i in 0 to 15 loop  -- 16 test cases
              a   <= ta(i);
              b   <= tb(i);
              wait for 1 ns;           -- propagating signals
              my_printout(a, b, prod, i);  -- write output
              wait for 1 ns;           -- other half of clock cycle
            end loop;  -- i
            wait;  -- never restart this process
          end process driver;
end architecture circuits; -- of tpmul8



