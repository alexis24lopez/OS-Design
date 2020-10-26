#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

#include "Assembler.h"
#include "VirtualMachine.h"

int main(int argc, char *argv[])
{
    Assembler as;
    VirtualMachine vm;

    if (argc == 1) {
        std::cout << "Must supply an assembly file name.\n";
        exit(1);
    }

    std::string assemblyFile = argv[1];
    int pos = assemblyFile.find(".");
    if (pos > assemblyFile.length() || assemblyFile.substr(pos) != ".s") {
        std::cout << "No .s suffix.\n";
        exit(2);
    }

    std::string name = assemblyFile.substr(0, pos);
    std::string objectFile = name + ".o";

    std::fstream assembly, objectCode;
    assembly.open(assemblyFile.c_str(), ios::in);
    objectCode.open(objectFile.c_str(), ios::out);
    if (!assembly.is_open() or !objectCode.is_open()) {
        std::cout << "Couldn't open " << assemblyFile << " and/or " << objectFile << std::endl;
        exit(3);
    }

    if (as.assemble(assembly, objectCode)) {
        std::cout << "Assembler Error\n";
        assembly.close();
        objectCode.close();
        exit(4);
    }

    assembly.close();
    objectCode.close();

    objectCode.open(objectFile.c_str(), ios::in);
    if (!objectCode.is_open()) {
        std::cout << "Couldn't open " << objectFile << std::endl;
        exit(5);
    }

    std::string inFile = name + ".in";
    std::string outFile = name + ".out";
    std::fstream in, out;
    in.open(inFile.c_str(), ios::in);
    out.open(outFile.c_str(), ios::out);
    if (!in.is_open() or !out.is_open()) {
        std::cout << "Couldn't open " << inFile << " and/or " << outFile << std::endl;
        exit(6);
    }

    vm.run(objectCode, in, out);
    out << "Clock = " << vm.get_clock() << std::endl;

    objectCode.close();
    in.close();
    out.close();

    return 0;
} // main