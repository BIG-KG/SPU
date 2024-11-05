all: hello

hello: main.o stackfunk.o const.o canary.o onegin.o
	g++ main.o stackfunk.o const.o canary.o onegin.o -O2 hell.exe

main.o: main.cpp
	g++ -c main.cpp

stackfunk.o: C:\MIPT\SPU\stack\stackfunk.cpp
	g++ -c C:\MIPT\SPU\stack\stackfunk.cpp

const.o: C:\MIPT\SPU\stack\const.cpp
	g++ -c C:\MIPT\SPU\stack\const.cpp

canary.o: C:\MIPT\SPU\stack\canary.cpp
	g++ -c C:\MIPT\SPU\stack\canary.cpp

onegin.o: C:\MIPT\SPU\onegin\onegin.cpp
	g++ -c C:\MIPT\SPU\onegin\onegin.cpp

clean:
	rm -rf *.o hello2
