CFLAGS = -g -Wall
CC = g++

objects = main.o brute.o genetic.o adjacencymatrix.o

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.cpp brute.cpp genetic.cpp adjacencymatrix.cpp

.PHONY : clean
clean:
	rm -f main $(objects)
	rm -f *.exe
	rm -f errReport.txt
	rm -f results.txt