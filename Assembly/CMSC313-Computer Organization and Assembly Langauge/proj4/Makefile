#
# Leave the following lines alone!!!

CFLAGS=-m32 -g -Wall -ansi
LDFLAGS=-melf_i386 -g
%.o: %.asm
	nasm -f elf -g -l $*.lst $< -o $@

#
# End of provided rules
#

# Modify following to the name of your linked program
TARGET=sort_books.out

# Modify following to the list of component object files
OBJS=sort_books.o bookcmp.o

#
# Do not modify remainder of this Makefile
#
${TARGET}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${TARGET}

 run:
	./sort_books.out

 clean:

	rm -rf *.o
	rm -f *.o*
	rm -f *.lst
	rm -f *~ *.h.gch *#
	rm -rf *.out
