FLAGS = -Wall -O2 --std=c++11
LINKS = -lGL -lGLU -lglut -lm

all: skatingdroid.o

skatingdroid.o: main.o skating.o
	g++ skating.o main.o -o skatingdroid.o ${FLAGS} ${LINKS}

main.o: main.cpp
	g++ -c main.cpp -o main.o ${FLAGS}

skating.o: skating.h skating.cpp
	g++ -c skating.cpp -o skating.o ${FLAGS}

clean:
	rm main.o skating.o skatingdroid.o
