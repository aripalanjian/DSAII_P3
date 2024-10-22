CFLAGS = -g -Wall
CC = g++

objects = 

main: $(objects)
	$(CC) -o main $(objects)

main.o: main.cpp

.PHONY : clean
clean:
	rm -f main $(objects)
	rm -f *.exe