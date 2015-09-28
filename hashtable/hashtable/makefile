all: hash-table

hash-table: main.o
	g++ main.o -o hash-table

main.0: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o hash-table
	