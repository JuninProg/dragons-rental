all: app

app: main.o warrior.o dragon.o element.o rent.o
	gcc -o app main.o warrior.o dragon.o element.o rent.o

main.o: main.c
	gcc -o main.o -c main.c

warrior.o: warrior.c warrior.h
	gcc -o warrior.o -c warrior.c

dragon.o: dragon.c dragon.h
	gcc -o dragon.o -c dragon.c

element.o: element.c element.h
	gcc -o element.o -c element.c

rent.o: rent.c rent.h
	gcc -o rent.o -c rent.c

clean: 
	rm -rf *.o && rm -rf app
