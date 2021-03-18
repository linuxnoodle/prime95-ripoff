CC=g++
CPPFLAGS=-O0 -std=c++11 -pthread

smasher: main.cpp
	$(CC) $(CPPFLAGS) main.cpp -o smasher

.PHONY: clean
clean:
	rm smasher
