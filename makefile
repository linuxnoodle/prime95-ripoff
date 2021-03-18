CC=g++
ifeq ($(OS), Windows_NT)
	CPPFLAGS=-O0 -std=c++11
else
	CPPFLAGS=-O0 -std=c++11 -pthread
endif

smasher: main.cpp
	$(CC) $(CPPFLAGS) main.cpp -o smasher

.PHONY: clean
clean:
	rm smasher
