all: terminal2.o mycp.o mygrep.o myls.o myps.o mymv.o
	gcc mycp.o mygrep.o myls.o mymv.o myps.o terminal2.o -o out.o -lreadline

mycp.o: mycp.c headers.h
	gcc -c mycp.c -o mycp.o

mymv.o: mymv.c headers.h
	gcc -c mymv.c -o mymv.o

myps.o: myps.c headers.h
	gcc -c myps.c -o myps.o

mygrep.o: mygrep.c headers.h
	gcc -c mygrep.c -o mygrep.o

myls.o: myls.c headers.h
	gcc -c myls.c -o myls.o

term.o: terminal2.c headers.h
	gcc -c terminal2.c -o terminal2.o