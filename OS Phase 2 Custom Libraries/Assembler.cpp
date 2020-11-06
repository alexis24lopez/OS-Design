#include <iostream>
#include <iomanip>
#include <fstream>
//#include <string>
#include <sstream>

#include "String.h"
#include "Assembler.h"

Assembler::Assembler()
{
}

int Assembler::assemble(std::fstream& in, std::fstream& out)
{
	String line;
    String opcode;
    int rd, rs, addr, constant;
    int instruction;

    const int success = false;
    const int error = true;
    //const int debug = false;

    getline(in, line);
    while (!in.eof()) {
        if (line[0] == '!' or line == "") {    // ignore comment or empty lines
            getline(in, line);
            continue;
        }

        istringstream str(line.c_str());
        str >> opcode;

        if (opcode == "load") {
	    	// Inputs as strings register destination and address location
            str >> rd >> addr;
            if (rd < 0 || rd > 3)
                return error;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 0;
            // Sets opcode at 15:11, register destination at 10:9,
            // and address at 8:0
            instruction = instruction | rd<<9 | addr;
        } else if (opcode == "loadi") {
			// Inputs as strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 0;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and constant value at 7:0
            instruction = instruction | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "store") {
	    // Inputs as strings register destination and address
            str >> rd >> addr;
            if (rd < 0 || rd > 3)
                return error;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 1;
            // Sets opcode at 15:11, register destination at 10:9.
            // immediate bit at 8, and address at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | addr;
        } else if (opcode == "add") {
			// Inputs as strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 2;
            // Sets opcode at 15:11, register destination at 10:9,
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "addi") {
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 2;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and a constant value at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "addc") {
			// Inputs strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 3;
            // Sets opcode at 15:11, register destination at 10:9,
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "addci") {
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 3;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and a constant value at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "sub") {
			// Inputs strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 4;
            // Sets opcode at 15:11, register destination at 10:9,
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "subi") {
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 4;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and a constant at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "subc") {
			// Inputs strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 5;
            // Sets opcode at 15:11, register destination at 10:9,
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "subci") {
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 5;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and a constant at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "and") {
			// Inputs strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 6;
            // Sets opcode at 15:11, register destination at 10:9, 
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "andi") {
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 6;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and a constant at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "xor") {
			// Inputs strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 7;
            // Sets opcode at 15:11, register destination at 10:9,
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "xori") {
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 7;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and a constant at 7:0	
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "compl") {
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 8;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "shl") {
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 9;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "shla") {
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 10;
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "shr")	{
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 11;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "shra") {
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 12;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "compr") {
			// Inputs strings register source and destination
            str >> rd >> rs;
            if (rd < 0 || rd > 3)
                return error;
            if (rs < 0 || rs > 3)
                return error;
            instruction = 13;
            // Sets opcode at 15:11, register destination at 10:9,
            // and register source at 7:6
            instruction = instruction<<11 | rd<<9 | rs<<6;
        } else if (opcode == "compri") {	
			// Inputs strings register destination and a constant
            str >> rd >> constant;
            if (rd < 0 || rd > 3)
                return error;
            if (constant < -128 || constant > 127)
                return error;
            instruction = 13;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and constant at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | (0xff & constant);
        } else if (opcode == "getstat") {
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 14;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "putstat")	{
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 15;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "jump") {
			// Inputs string address
            str >> addr;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 16;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and address at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | addr;
        } else if (opcode == "jumpl") {
			// Inputs string address
            str >> addr;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 17;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and address at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | addr;
        } else if (opcode == "jumpe") {
			// Inputs string address
            str >> addr;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 18;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and address at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | addr;
        } else if (opcode == "jumpg") {
			// Inputs string address
            str >> addr;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 19;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and address at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | addr;
        } else if (opcode == "call") {
			// Inputs string address
            str >> addr;
            if (addr < 0 || addr > 255)
                return error;
            instruction = 20;
            // Sets opcode at 15:11, register destination at 10:9,
            // immediate bit at 8, and address at 7:0
            instruction = instruction<<11 | rd<<9 | 1<<8 | addr;
        } else if (opcode == "return") {
            instruction = 21;
            // Sets opcode at 15:11
            instruction = instruction<<11;
        } else if (opcode == "read") {
			// Inputs string register destination
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 22;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "write") {
			// Inputs strings register destination	
            str >> rd;
            if (rd < 0 || rd > 3)
                return error;
            instruction = 23;
            // Sets opcode at 15:11 and register destination at 10:9
            instruction = instruction<<11 | rd<<9;
        } else if (opcode == "halt") {
            instruction = 24;
            // Sets opcode at 15:11
            instruction = instruction<<11;
        } else if (opcode == "noop") {
            instruction = 25;
            // Sets opcode at 15:11
            instruction = instruction<<11;
        }
	    else
            return error;

        out << setfill('0') << setw(5) << instruction << std::endl;
        getline(in, line);
    }
    return success;
} // assemble