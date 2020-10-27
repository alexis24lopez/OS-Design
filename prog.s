load 1 9		! r[1] = mem[9]	00521
load 2 9		! r[2] = mem[9]	01033
loadi 2 -123	! r[2] = -123 (set reg 2)	01413
loadi 2 71		!01351
add 0 3			! r[0] += r[3]	04288
addi 0 -56		! r[0] += -56	04552
jump 10			! pc = 10 (runtime error)    	33034
store 2 20		! m[20] = r[2] (runtime error)    	03348
halt			!49152
noop			!51200
