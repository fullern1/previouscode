# Makefile for Cadence "inca" "ncvhdl"  VHDL
#
# use  tcsh
#      source vhdl_cshrc
#      make
#
# must have set up  cds.lib  and  hdl.var  in default directory
# must have subdirectory "vhdl_lib",  mkdir  vhdl_lib, or just  make clean 

all: add32_test.out tadd32.out pmul8_test.out part1.out part2a.out part2b.out

part2b.out: part2b.vhdl add32.vhdl bshift.vhdl part2b.run part2b.abs
	ncvhdl -v93 add32.vhdl
	ncvhdl -v93 bshift.vhdl
	ncvhdl -v93 pmul8.vhdl
	ncvhdl -v93 divcas16.vhdl
	ncvhdl -v93 part2b.vhdl  # renamed and modified part2a.vhdl
	ncelab -v93 part2b:schematic
	ncsim  -batch -logfile part2b.out -input part2b.run part2b

part2a.out: part2a.vhdl add32.vhdl bshift.vhdl part2a.run part2a.abs
	ncvhdl -v93 add32.vhdl
	ncvhdl -v93 bshift.vhdl
	ncvhdl -v93 pmul8.vhdl
	ncvhdl -v93 divcas16.vhdl
	ncvhdl -v93 part2a.vhdl  # renamed and modified part1.vhdl
	ncelab -v93 part2a:schematic
	ncsim  -batch -logfile part2a.out -input part2a.run part2a

part1.out: part1.vhdl add32.vhdl bshift.vhdl pmul8.vhdl divcas16.vhdl part1.run part1.abs
	ncvhdl -v93 add32.vhdl
	ncvhdl -v93 bshift.vhdl
	ncvhdl -v93 pmul8.vhdl
	ncvhdl -v93 divcas16.vhdl
	ncvhdl -v93 part1.vhdl  # renamed and modified part1_start.vhdl
	ncelab -v93 part1:schematic
	ncsim  -batch -logfile part1.out -input part1.run part1

pmul8_test.out: pmul8.vhdl pmul8_test.vhdl pmul8_test.run
	ncvhdl -v93 pmul8.vhdl
	ncvhdl -v93 pmul8_test.vhdl
	ncelab -v93 pmul8_test:circuits
	ncsim -batch -logfile pmul8_test.out -input pmul8_test.run pmul8_test

add32_test.out:  add32_test.vhdl add32_test.run
	ncvhdl -v93 add32_test.vhdl
	ncelab -v93 add32_test:circuits
	ncsim -batch  -logfile add32_test.out -input add32_test.run add32_test

tadd32.out: add32.vhdl tadd32.vhdl tadd32.run
	ncvhdl -v93 add32.vhdl
	ncvhdl -v93 tadd32.vhdl
	ncelab -v93 tadd32:circuits
	ncsim -batch -logfile tadd32.out -input tadd32.run tadd32

clean:
	rm -f *.log
	rm -rf vhdl_lib
	mkdir  vhdl_lib


