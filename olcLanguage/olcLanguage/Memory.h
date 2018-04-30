#pragma once
enum CommandType {
	Load, // Load from ram
	LoadC,
	LoadI,
	Store, // Store in ram
	StoreI,
	Add, // Add
	AddC,
	AddI,
	Subtract, // Subtract (SubtractC is missing since it's redundant, 
			  // because SubtractC value  is the same as  AddC -value)
			  // However, I will add that command into the assembly interpreter
	SubtractI,
	Compare, // Compare
	CompareC,
	CompareI,
	Goto, // Go to other commands
	BranchEqual,
	BranchNotEqual,
	BranchGreater,
	BranchGreaterEqual,
	BranchLess,
	BranchLessEqual,
	BranchCarry,
	BranchOverflow,

	Print, // Temporary debug command, will eventually be removed
	Terminate,
};

struct Command {
	CommandType T;
	int Value;

	Command(CommandType t, int value) {
		T = t;
		Value = value;
	}
};

class Memory {
public:
	Command* commands;
	int* ram;
};