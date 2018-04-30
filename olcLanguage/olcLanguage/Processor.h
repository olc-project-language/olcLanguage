#pragma once
#include "Memory.h";

class Processor {
public:
	void RunClock();
	bool active = true;

	Processor(Memory ram, int startIndex);

	// Integer unit
	int data;
	int address = 0;
	bool zBit;
	bool nBit;

	int MBR;
	int index;

	Memory ram;
private:
	int Add(int a, int b);
};