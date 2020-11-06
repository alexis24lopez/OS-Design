os_main: os_main.o OS.o VirtualMachine.o Assembler.o String.o
	g++ -o os_main os_main.o OS.o VirtualMachine.o Assembler.o String.o

os_main.o: os_main.cpp
	g++ -g -c os_main.cpp

OS.o: OS.cpp OS.h
	g++ -g -c OS.cpp

VirtualMachine.o: VirtualMachine.cpp VirtualMachine.h String.cpp String.h
	g++ -g -c VirtualMachine.cpp String.cpp

Assembler.o: Assembler.cpp Assembler.h String.cpp String.h
	g++ -g -c Assembler.cpp String.cpp

clean:
	rm *.o os
