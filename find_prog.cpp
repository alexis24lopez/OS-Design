#include<iostream>
#include<fstream>
#include<cassert>
#include<string>
#include <iomanip>
#include <cstdlib>

int main()
{
	system("dir *.s > progs1");
	std::fstream progs1;
	progs1.open("progs1", std::ios::in);
	assert(progs1.is_open());
	
	std::string programs = "";
	std::fstream progs("progs", std::ios::out);
	while(progs1 >> programs){
		for (int i = 0; i < programs.size(); ++i){
			if(programs[i] == '.'){
				std::cout << programs << std::endl;
				progs << programs << std::endl;
			}
		}
			
	}
	progs.close();
}

