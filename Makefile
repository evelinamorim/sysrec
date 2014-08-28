datadir = ../ml-100k/

compile:
	g++ -O3 -c -o main.o main.cpp -ggdb
	g++ -O3 -c -o util.o util.cpp -ggdb
	g++ -O3 -c -o le.o le.cpp -ggdb
	g++ -O3 -o tp1 main.o util.o le.o -g

run: $(datadir)
	./tp1 $(datadir)/u.user $(datadir)/u.item $(datadir)/ua.base
