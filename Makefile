.PHONY: all clean

all: main

clean:
		rm -rf mylib *.o *.log
logwriter.so: src/logwriter.cpp include/logwriter.hpp
		g++ -fpic -shared src/logwriter.cpp -Iinclude -o liblogwriter.so
main: logwriter.so
		g++ src/main.cpp -o main -Iinclude -llogwriter -L.

