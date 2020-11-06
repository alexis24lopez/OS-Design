read 0		! Reading from .in file to r[0] (VALUE)
read 1		! Reading from .in file to r[1] (COUNTER)
add 2 0		! Set r[2] = r[0] read value.
add 3 2		! (line 3) LOOP: keep adding r[2] until counter ==0
subi 1 1	! r[1] = r[1] - 1 (subtract counter)
compri 1 0	! if r[1] (COUNTER) == 0 ? finish : keep mult
jumpg 3		! Continue looping
write 3		! (line 8) Save result
halt
