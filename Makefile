all: main.o

main.o: main.cpp
	g++ main.cpp -o main.o -Wall -O2 -lGL -lGLU -lglut -lm

clean:
	rm main.o
