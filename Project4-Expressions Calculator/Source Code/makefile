main: Calculator.o Main.o SuperBinaryOperation.o
        g++ -o MyCalculator Calculator.o Main.o SuperBinaryOperation.o
MyCalculator.o: Calculator.cpp Calculator.h
        g++ -c -o Calculator.o Calculator.cpp
Main.o: Main.cpp Calculator.h
        g++ -c -o Main.o Main.cpp
SuperBinaryOperation.o: SuperBinaryOperation.cpp Calculator.h
        g++ -c -o SuperBinaryOperation.o SuperBinaryOperation.cpp
