#include <iostream>
#include <conio.h>
#include "Memory.h";
#include "Processor.h";

// This is the virtual machine that runs a pre-compiled program
// Please 
int main() {
	Memory m;
	m.commands = new Command[9]{
		Command(Load, 0), // Print A
		Command(Print, 0),
		Command(Add, 1), // C = A + B
		Command(Store, 2),
		Command(Load, 1), // A = B
		Command(Store, 0),
		Command(Load, 2), // B = C
		Command(Store, 1),
		Command(Goto, -1),
	};
	m.ram = new int[3]{ 1, 1, 0 };

	Processor p(m, 0);

	while (p.active) {
		p.RunClock();
		getch();
	}

	getch();

	return 0;
}