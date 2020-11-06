#include<iostream>
#include <string>
#include <sstream>

int main()
{
	/*int rd = 1;
	
	int dest = 0 | rd<<9 | 9;
	
	std::cout << dest << std::endl;*/
	
	
	std::string opcode;
	std::string rd;
	std::string addr;
	
	std::string values = "load 1 9";
	std::istringstream str(values);
	
	str >> opcode;
	
	if(opcode == "load"){
		str >> rd;
		if(rd == "1"){
			str >> addr;
			if(addr == "9"){
				std::cout << "it works!" << std::endl;
			}
		}
	}
	
}