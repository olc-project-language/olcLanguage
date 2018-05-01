#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include "Memory.h"
#include "Processor.h"
#include "AssemblyInterpreter.h"

std::string slurp(std::ifstream* in) {
	std::stringstream sstr;
	sstr << in->rdbuf();
	return sstr.str();
}

// This is the virtual machine that runs a pre-compiled program
// Please 
int main(int argc,      // Number of strings in array argv  
		 char *argv[],   // Array of command-line argument strings  
		 char *envp[]) {

	InitializeInterpretation();

	std::string data = "Terminate;";

	if (argc >= 2) {
		std::ifstream assembly;
		assembly.open(argv[1]);
		if (assembly.is_open()) {
			std::ifstream * assemblyPtr = &assembly;
			data = slurp(assemblyPtr);
		}
		assembly.close();
	}
	else {
		std::cout << "I would suggest opening a text file containing\nassembly code" << std::endl;
		getch();
		return 0;
	}

	Memory m;
	m.commands = InterpretString(data);
	m.ram = new int[300];

	Processor p(m, 0);

	int max_ticks = 30000;
	int ticks = 0;
	while (p.active && ticks < max_ticks) {
		p.RunClock();
		ticks++;
	}

	getch();

	return 0;
}