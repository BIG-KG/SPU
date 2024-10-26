all: hello
	hello4
hello: C:\MIPT\stack\main.o stackfunk.o const.o canary.o 
	g++ C:\MIPT\stack\main.o stackfunk.o const.o canary.o  -o hello4

main.o: main.cpp
	g++ -c main.cpp
	
stackfunk.o: stackfunk.cpp
	g++ -c stackfunk.cpp
	
const.o: const.cpp
	g++ -c const.cpp
	
canary.o: canary.cpp
	g++ -c canary.cpp

clean:
	rm -rf *.o hello