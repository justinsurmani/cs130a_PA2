all: prog1

prog1: Quash.cpp Quash.h
	g++ -o prog1 Quash.cpp Quash.h

