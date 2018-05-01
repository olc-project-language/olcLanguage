#pragma once
#include "Memory.h"
#include <map>
#include <string>
#include <iterator>
#include <iostream>

std::map<std::string, CommandType> parseMap;

void InitializeInterpretation() {
	parseMap["Load"] = CommandType::Load;
	parseMap["LoadC"] = CommandType::LoadC;
	parseMap["LoadI"] = CommandType::LoadC;
	parseMap["Store"] = CommandType::Store;
	parseMap["StoreI"] = CommandType::Store;
	parseMap["Add"] = CommandType::Add;
	parseMap["AddC"] = CommandType::AddC;
	parseMap["AddI"] = CommandType::AddI;
	parseMap["Sub"] = CommandType::Subtract;
	parseMap["SubI"] = CommandType::SubtractI;
	parseMap["Compare"] = CommandType::Compare;
	parseMap["CompareC"] = CommandType::CompareC;
	parseMap["CompareI"] = CommandType::CompareI;
	parseMap["Goto"] = CommandType::Goto;
	parseMap["Beq"] = CommandType::BranchEqual;
	parseMap["Bne"] = CommandType::BranchNotEqual;
	parseMap["Bgt"] = CommandType::BranchGreater;
	parseMap["Bge"] = CommandType::BranchGreaterEqual;
	parseMap["Blt"] = CommandType::BranchLess;
	parseMap["Ble"] = CommandType::BranchLessEqual;
	parseMap["Terminate"] = CommandType::Terminate;

	parseMap["Print"] = CommandType::Print;
}

Command* InterpretString(std::string parsing) {

	// Find the number of commands
	int nCommands = 0;
	for (int i = 0; parsing[i] != '\0'; i++) {
		if (parsing[i] == ';')
			nCommands++;
	}

	// Create and populate the commands array
	Command* commands = new Command[nCommands];

	bool lookForCommand = true;
	bool lookForValue = false;
	int substrStart = -1;
	int n_command = 0;

	std::string command_name;
	int command_value = -1;
	for (int i = 0; parsing[i] != '\0'; i++) {
		if ((lookForCommand || lookForValue) && substrStart < 0) {
			if (parsing[i] != ' ' && parsing[i] != '\n') {
				substrStart = i;
			}
		}
		
		if (lookForCommand && substrStart >= 0) {
			if (parsing[i] == ' ' || parsing[i] == '\n' || 
				parsing[i] == ';' || parsing[i] == ':') {
				command_name = parsing.substr(substrStart, i - substrStart);
				lookForCommand = false;
				substrStart = -1;
			}
		}
		else if (lookForValue && substrStart >= 0) {
			if (parsing[i] == ' ' || parsing[i] == '\n' || 
				parsing[i] == ';') {
				std::string str_value = parsing.substr(substrStart, i - substrStart);
				command_value = std::stol(str_value, nullptr, 0);
				lookForValue = false;
				substrStart = -1;
			}
		}
		
		if (parsing[i] == ':') {
			lookForValue = true;
		}

		if (parsing[i] == ';') {
			lookForCommand = true;

			// Add the command to the array
			commands[n_command].T = parseMap[command_name];

			commands[n_command].Value = command_value;

			//std::cout << command_name << " : " << command_value << std::endl;
			command_value = -1;
			n_command++;
		}
	}

	return commands;
}