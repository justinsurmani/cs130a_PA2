all: prog1.out

prog1.out: Quash.cpp Quash.h
	g++ -o prog1.out Quash.cpp Quash.h

