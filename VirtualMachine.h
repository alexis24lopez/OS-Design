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
public:
    VirtualMachine(): msize(256), rsize(4), clock(0) 
    { 
        mem = std::vector<int>(msize); 
        r = std::vector<int>(rsize); 
    }
    void run(std::fstream&, std::fstream&, std::fstream&);
    int get_clock();
}; // VirtualMachine

#endif