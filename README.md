# OS-Design
Created a basic 16-bit OS using C++ as main language. It simulated a 16-bit CPU.

For more information about how the OS is designed, instruction set, run and write programs refer
to A 16-bit OS system specification a docx file.

Note: if you have installed c++ and make, you can just compile the makefile and then run the os. 
      As shown in the picture on folder OS INFO.
      
Note: If you're running the OS in linux you need to uncomment line: 16 on OS.cpp
      and change system("dir *.s > progs") -> system("ls *.s > progs). That would
      gather all the *.s files. If running in linux you don't need to run
      find_prog.cpp because system("ls *.s > progs) does it for you! On
      windows leave line: 16 on OS.cpp as it is and follow instructions on
      Run_OS_Phase2.png located on OS Info.

Note: If you want to run OS Phase2 Custom Libraries OS it includes my own 
      String, Vector, Queue, List libraries to run my OS. This means I'm
      not using the std: string, vector, queue, list template libraries.
      You can still uncomment my own custom libraries and use the std.
      If using std libraries change String -> std::string, 
      Vector -> std::vector, Queue -> std::queue, List -> std::list.

Enjoy the show!
