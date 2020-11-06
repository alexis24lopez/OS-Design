#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <fstream>
//#include <vector>

#include "Vector.h"

class VirtualMachine {
    int msize;
    int rsize;
    int pc, ir, sr, sp, clock;
    Vector<int> mem;
    Vector<int> r;
    int base, limit;
	int total_limit;
public:
    VirtualMachine(): msize(256), rsize(4), clock(0) 
    { 
        mem = Vector<int>(msize); 
        r = Vector<int>(rsize); 
    }
    void load(std::fstream&, int base, int & limit);
    void run(int time_slice);
	
	friend class OS;
}; // VirtualMachine

#endif