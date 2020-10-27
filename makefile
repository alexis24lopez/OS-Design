os_main: os_main.o OS.o VirtualMachine.o Assembler.o
	g++ -o os_main os_main.o OS.o VirtualMachine.o Assembler.o

os_main.o: os_main.cpp
	g++ -g -c os_main.cpp

OS.o: OS.cpp OS.h
	g++ -g -c OS.cpp

VirtualMachine.o: VirtualMachine.cpp VirtualMachine.h
	g++ -g -c VirtualMachine.cpp

Assembler.o: Assembler.cpp Assembler.h
	g++ -g -c Assembler.cpp

clean:
	rm *.o os
