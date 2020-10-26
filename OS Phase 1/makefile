os: os.o Assembler.o VirtualMachine.o
	g++ -o os os.o Assembler.o VirtualMachine.o

os.o: os.cpp
	g++ -c os.cpp

VirtualMachine.o: VirtualMachine.cpp VirtualMachine.h
	g++ -c VirtualMachine.cpp

Assembler.o: Assembler.cpp Assembler.h
	g++ -c Assembler.cpp

.PHONY: clean
clean:
	del *.o os
