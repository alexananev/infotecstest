.PHONY: all clean run

all: main

clean:
		rm -rf *.o
logwriter.so: src/logwriter.cpp include/logwriter.hpp
		g++ -fpic -shared src/logwriter.cpp -Iinclude -o liblogwriter.so
main: logwriter.so
		g++ src/main.cpp -o main -Iinclude -llogwriter -L.
run: main
		LD_LIBRARY_PATH=. ./main file.log INFO
