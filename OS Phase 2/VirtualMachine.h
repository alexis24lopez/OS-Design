#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <fstream>
#include <vector>

class VirtualMachine {
    int msize;
    int rsize;
    int pc, ir, sr, sp, clock;
    std::vector<int> mem;
    std::vector<int> r;
    int base, limit;
	int total_limit;
public:
    VirtualMachine(): msize(256), rsize(4), clock(0) 
    { 
        mem = std::vector<int>(msize); 
        r = std::vector<int>(rsize); 
    }
    void load(std::fstream&, int base, int & limit);
    void run(int time_slice);
	
	friend class OS;
}; // VirtualMachine

#endif