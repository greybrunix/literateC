
CC=tcc
CCFLAGS=-std=C89 -pedantic -O2 -Wall -Wpedantic -g

all: ./obj/literateC.o
	${CC} ${CCFLAGS} -o ./bin/literateC ./obj/literateC.o



install: ./obj/literateC.o
	${CC} ${CCFLAGS} -o ./bin/literateC ./obj/literateC.o
	sudo mv ./bin/literateC /usr/bin/literateC
	echo man page missing

./obj/literateC.o: ./src/main.c
	${CC} ${CCFLAGS} -c ./src/main.c -o ./obj/literateC.o

uninstall:
	sudo rm -f /usr/bin/literateC
	echo man page missing

clean:
	rm bin/literateC; touch bin/literateC
	rm obj/*
