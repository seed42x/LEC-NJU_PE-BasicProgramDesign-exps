main: Helper.o Function.o Main.o
	g++ -o MySQL Helper.o Function.o Main.o -g

Helper.o: Helper.cpp General.h
	g++ -c -o Helper.o Helper.cpp
Function.o: Function.cpp General.h
	g++ -c -o Function.o Function.cpp
Main.o: Main.cpp General.h
	g++ -c -o Main.o Main.cpp
