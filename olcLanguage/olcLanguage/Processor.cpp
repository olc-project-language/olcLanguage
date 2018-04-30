#include "Processor.h"
#include <iostream>

Processor::Processor(Memory ram, int startIndex) {
	this->ram = ram;
	this->index = startIndex;
}

void Processor::RunClock() {
	if (!active)
		return;

	switch (ram.commands[index].T) {
		case CommandType::Load:
			data = ram.ram[address + ram.commands[index].Value];
			break;
		case CommandType::LoadC:
			data = ram.commands[index].Value;
			break;
		case CommandType::LoadI:
			data = ram.ram[address + ram.ram[address + ram.commands[index].Value]];
			break;

		case CommandType::Store:
			ram.ram[address + ram.commands[index].Value] = data;
			break;
		case CommandType::StoreI:
			ram.ram[ram.ram[ram.commands[index].Value]] = data;
			break;

		case CommandType::Add:
			data = Add(data, ram.ram[address + ram.commands[index].Value]);
			break;
		case CommandType::AddC:
			data = Add(data, ram.commands[index].Value);
			break;
		case CommandType::AddI:
			data = Add(data, ram.ram[address + ram.ram[address + ram.commands[index].Value]]);
			break;

		case CommandType::Subtract:
			data = Add(data, -ram.ram[address + ram.commands[index].Value]);
			break;
		case CommandType::SubtractI:
			data = Add(data, -ram.ram[address + ram.ram[address + ram.commands[index].Value]]);
			break;

		case CommandType::Compare:
			Add(data, -ram.ram[address + ram.commands[index].Value]);
			break;
		case CommandType::CompareC:
			Add(data, ram.commands[index].Value);
			break;
		case CommandType::CompareI:
			Add(data, -ram.ram[address + ram.ram[address + ram.commands[index].Value]]);
			break;

		case CommandType::Goto:
			index = address + ram.commands[index].Value;
			break;

		case CommandType::Print:
			std::cout << data << std::endl;
			break;
		default:
			active = false;
			std::cout << "Terminated program\n";
			return;
	}

	index++;
}

int Processor::Add(int a, int b) {
	int result = a + b;
	zBit = result == 0;
	nBit = result < 0;
	return result;
}