EXENAME=juegotest
FLAGS=-Wall -Werror -std=c99 -Wconversion
ZIPNAME=TP3-entrega
COPYDIR=~/Documents

clear:
	clear

compile:
	gcc *.c *.o ${FLAGS} -o ${EXENAME}

compile-nf:
	gcc *.c *.o -o ${EXENAME}

compile-gdb:
	gcc *.c *.o -o ${EXENAME}debug -g

run:
	./${EXENAME}

clean-bin:
	rm -f ./${EXENAME}

clean-zip:
	rm -f ./${ZIPNAME}

clean-all: clean-bin clean-zip

cycle: clean-bin clear compile run

debug:
	gdbtui ./${EXENAME}debug

cycle-nf: clean clear compile-nf run

copy:
	cp ${ZIPNAME}.zip ${COPYDIR}/${ZIPNAME}.zip

compress:
	zip ${ZIPNAME} *.c *.h *.o

hand-in: clean-zip compress copy