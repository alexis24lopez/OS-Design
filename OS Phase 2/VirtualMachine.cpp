#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <cassert>

#include "VirtualMachine.h"

void VirtualMachine::load(std::fstream& objectCode, int base, int & limit)
{
    for (limit = base; objectCode >> mem[limit]; limit++);
}

void VirtualMachine::run(int time_slice)
{
    const int debug = false;
    int opcode, rd, i, rs, constant, addr, j;

    int interrupt = clock + time_slice;

    while (pc < base + limit and clock < interrupt) {
        ir = mem[pc];
        pc++;
        opcode = (ir&0xf800)>>11;
        rd = (ir&0x600)>>9;
        i = (ir&0x100)>>8;
        rs = (ir&0xc0)>>6;
        addr = ir&0xff;
        constant = addr;
    
        clock++;
    
        if (opcode == 0) {    /* load loadi */
            if (i) {
                if (constant&0x80) constant |= 0xff00;
				// Loads an immediate value into a register
                r[rd] = constant; 
            } else {
                if (addr >= limit) {
					// Checks if address stays within Mem size
                    sr &= 0x1f; 
					sr |= 0x40; // out of bound ref
                    return;
                }
				// Get's a value from an address in memory and loads it in a register
                r[rd] = mem[addr+base];
                clock += 3;
            }

        } else if (opcode == 1) {     /* store */
            if (addr >= limit) {
                sr &= 0x1f; 
				sr |= 0x40; // out of bound ref
                return;
            }
			// Get's a value from a register and stores it in an address of memory
            mem[addr+base] = r[rd];
            clock += 3;

        } else if (opcode == 2) {    /* add addi */
			// Gets MSB for sign1
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
				// Gets MSB for sign2
                sign2 = (constant&0x80)>>7;
                // sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
				// Adds a constant value to the register destination
                r[rd] = r[rd] + constant;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
				// Adds value of register destination with another value in a register 
                r[rd] = r[rd] + temp;
            }

            // set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // set OVERFLOW
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15) sr |= 0x10;
            else sr &= 0xffef;

            // keep it at 16 bits
            r[rd] &= 0xffff;
        } else if (opcode == 3) {   /* addc addci */
			// Gets MSB for sign1
            int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
	    		// Gets MSB for sign2
                sign2 = (constant&0x80)>>7;
                // Sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                // Adds value of register destination with a constant
                // and CARRY
                r[rd] = r[rd] + constant + sr&0x1;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // Sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                // Adds value of register destination with value of
                // source register and CARRY
                r[rd] = r[rd] + temp + sr&0x1;
            }

            // Set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // Set OVERFLOW
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15) sr |= 0x10;
            else sr &= 0xffef;

            // Keep it at 16 bits
            r[rd] &= 0xffff;
        } else if (opcode == 4) {    /* sub subi */
	
			int sign1 = (r[rd]&0x8000)>>15;
			int sign2;
			if(i) {
	    		sign2 = (constant&0x80)>>7;
				//sign extend both operands to perform operation
				if (sign2) constant |= 0xffffff00;
				if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
				// Subtracts a constant with value in register destination
				r[rd] = r[rd] - constant;
			} else {
				sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
				// Subtracts a value in register source with value in register destination
                r[rd] = r[rd] - temp;  
			}
			// set CARRY
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // set OVERFLOW
    	    // If both sign1 and sign2 are positive numbers and result is negative
    	    // then OVERFLOW occurs and vice versa
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15)
                sr |= 0x10;
            else
                sr &= 0xffef;

            // keep it at 16 bits
            r[rd] &= 0xffff;
		} else if (opcode == 5) {   /* subc subci */
	
			// Get MSB for sign1
			int sign1 = (r[rd]&0x8000)>>15;
            int sign2;
            if (i) {
				// Gets MSB for sign2
                sign2 = (constant&0x80)>>7;
                // Sign extend both operands to perform operation
                if (sign2) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                // Subtracts value of register destination with a constant 
                // and CARRY
                r[rd] = r[rd] - constant - sr&0x1;
            } else {
                sign2 = (r[rs]&0x8000)>>15;
                int temp = r[rs];
                // Sign extend both operands to perform operation
                if (sign2) temp |= 0xffff0000;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                // Subtracts value of register destination with value of
                // register source and CARRY
                r[rd] = r[rd] - temp - sr&0x1;
            }

            // Set CARRY in sr
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // Set OVERFLOW in sr
            if (sign1 == sign2 and sign1 != (r[rd]&0x8000)>>15) sr |= 0x10;
            else sr &= 0xffef;

            // Keep it at 16 bits
            r[rd] &= 0xffff;
		} else if (opcode == 6) {    /* and andi */
	
			if(i) {
				// Perform AND to the value of register destination
                // with a constant
				r[rd] = r[rd] & constant;
			} else {
                // Perform AND to the value of register destination 
                // with the value of register source
				r[rd] = r[rd] & r[rs];
			}
		}
		else if (opcode == 7) {   /* xor xori */

			if(i) {
				// Sign extend both operands to perform operation
                if (constant&0x80) constant |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
                // Perform XOR to the value of register destination
                // with a constant 
				r[rd] = r[rd] ^ constant;
			} else {
				// Sign extend both operands to perform operation
                if (r[rs] & 0x8000) r[rs] |= 0xffffff00;
                if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
				// Perform XOR to the value of register destination
				// with the value of register source
				r[rd] = r[rd] ^ r[rs];
			}
            // Keep it at 16 bits
            r[rd] &= 0xffff;
		} else if (opcode == 8) {   /* compl */
            // Sign extend the operand to perform operation
			if(r[rd] & 0x8000) r[rd] |= 0xffff0000;
			// Takes the compliment of the value of register destination
			r[rd] = ~r[rd];

            // Keep it at 16 bits
            r[rd] &= 0xffff;
		} else if (opcode == 9) {   /* shl */

            // set CARRY
            if (r[rd]&0x10000) 
	        sr |= 0x1;
            else sr &= 0xfffe;

			// Shifting left the value of the register destionation
			// by 1 is the same as multipling it by 2
			r[rd] = r[rd] << 1;
		} else if (opcode == 10) {   /* shla */
			// Gets MSB for sign1
			int sign1 = (r[rd]&0x8000)>>15;

			// Sign extend both operands to perform operation
			if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
			// Shifting left the value of the register destination
			// by 1 is the same as multiplying it by 2
			r[rd] = r[rd]*0x2;

			if (sign1 != (r[rd]&0x8000)>>15) {
				// If signs aren't equal perform OR with register
				// destination and 0x8
				r[rd] |= 0x8000;
			}

            // Set CARRY in sr
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // Keep it at 16 bits
            r[rd] &= 0xffff;
		} else if (opcode == 11) {   /* shr */
	
            // set CARRY
            if (r[rd]&0x1) sr |= 0x1;

            else sr &= 0xfffe;
			// Divide the value in the register destination by 2
			r[rd] = r[rd] >>1;
		} else if (opcode == 12) {   /* shra */

			// Gets MSB for sign1
			int sign1 = (r[rd]&0x8000)>>15;
			// Sign extend both operands to perform operation
			if (r[rd] & 0x8000) r[rd] |= 0xffff0000;
			// Divide the value in the register destination by 2
			r[rd] = r[rd]/0x2;

			if (sign1 != (r[rd]&0x8000)>>15) {
	        // If signs aren't equal perform OR with register
	        // destination and 0x8
			r[rd] |= 0x8000;
			}

            // Set CARRY in sr
            if (r[rd]&0x10000) sr |= 0x1;
            else sr &= 0xfffe;

            // Keep it at 16 bits
            r[rd] &= 0xffff;
		} else if (opcode == 13) {   /* compr compri */

			if(i) {
				// Compare both operands and set status register
				if (r[rd] < constant) {
					// Set Less, reset Equal and Greater
					sr &= 0x11;
					sr |= (1 << 3);
				} else if (r[rd] == constant) {
					// Set Equal, reset Less and Greater in sr
					sr &= 0x11;
					sr |= (1 << 2);
				} else {	// (r[rd] > constant)
					// Set Greater, reset Less and Equal in sr
					sr &= 0x11;
					sr |= (1 << 1);
				}
			} else {
				// compare both operands and set status register
				if (r[rd] < r[rs]) {
					//set Less, reset Equal and Greater
					sr &= 0x11;
					sr |= (1 << 3);
				} else if (r[rd] == r[rs]) {
					//set Equal, reset Less and Greater
					sr &= 0x11;
					sr |= (1 << 2);
				} else {	// (r[rd] > r[rs])
					//set Greater, reset Less and Equal
					sr &= 0x11;
					sr |= (1 << 1);
				}
			}
		} else if (opcode == 14) {   /* getstat */
			// Get sr and assign it to register destination
			r[rd] = sr;
		} else if (opcode == 15) {   /* putstat */
            // Get register destination and assign it to sr
			sr = r[rd];
		} else if (opcode == 16) {   /* jump */
			if (addr >= limit) {
                sr &= 0x1f; 
				sr |= 0x40; // Out-of-bound Reference
                return;
            }
			// Unconditional jump assigns next address to pc 
			pc = addr+base;
		} else if (opcode == 17) {   /* jumpl */
			if (addr >= limit) {
                sr &= 0x1f; 
				sr |= 0x40; // Out-of-bound Reference
                return;
            }
			// Checks if Less = 1 in sr, then assigns next address to pc
			if ((sr&0x8)>>3 == 1) pc = addr+base;

		} else if (opcode == 18) {   /* jumpe */
			if (addr >= limit) {
                sr &= 0x1f; 
				sr |= 0x40; // Out-of-bound Reference
                return;
            }
    	    // Checks if Equal = 1 in sr, then assigns next address to pc
			if ((sr&0x4)>>2 == 1) pc = addr+base;

		} else if (opcode == 19) {   /* jumpg */
			if (addr >= limit) {
                sr &= 0x1f; 
				sr |= 0x40; // Out-of-bound Reference
                return;
            }
			// Checks if Greater = 1 in sr, then assigns next address to pc
			if ((sr&0x2)>>1 == 1) pc = addr+base;
		} else if (opcode == 20) {   /* call */
			// Pushes pc to Mem[255]
			mem[--sp] = pc;
			for (int i = 0; i <= 3; i++) {
				// Pushes r0-r3 to Mem[254-251]
				mem[--sp] = r[i];
			}
			// Pushes sr to Mem[250]  
			mem[--sp] = sr;
			pc = addr+base;
			clock += 3;

		} else if (opcode == 21) {   /* return */
			// Pops sr from Mem[250]
			sr = mem[sp++];
			for (int i = 3; i >= 0; i--) {
				// Pops r3-r0 from Mem[251-254]
				r[i] = mem[sp++];
			}
			// Pops pc from Mem[255] 
			pc = mem[sp++];
			clock += 3;

		} else if (opcode == 22) {   /* read */
			sr &= 0x1f; 
            sr |= 0xc0; // Read
            sr |= rd<<8; // Register
            return;

		} else if (opcode == 23) {   /* write */
            sr &= 0x1f; 
            sr |= 0xe0; // Write
            sr |= rd<<8; // Register
            return;
		} else if (opcode == 24) {   /* halt */
			sr &= 0x1f; 
			sr |= 0x20; // Halt
			break;
		} else if (opcode == 25) {   /* noop */
			// Does nothing
		} else {
            std::cerr << "Bad opcode = " << opcode << std::endl;
            sr &= 0x1f; sr |= 0xa0; // Bad Opcode
            return;
        }

        if (debug) {
            printf("ir=%d op=%d rd=%d i=%d rs=%d const=%d addr=%d\n", ir, opcode, rd, i, rs, constant, addr);
            printf("r[0]=%d r[1]=%d r[2]=%d r[3]=%d pc=%d sr=%d sp=%d clock=%d\n\n", r[0], r[1], r[2], r[3], pc, sr, sp, clock);
        }
    }

    if (debug) {
        for (j=0; j<total_limit; j++) {
            printf("%8d", mem[j]);
            if ((j%8)==7) printf("\n");
        }
        std::cout << std::endl;
    }

    if (pc >= base+limit) {
        sr &= 0x1f; sr |= 0x40; // Out-of-bound Reference
    } else sr &= 0x1f; // Time Slice
} /* main */
