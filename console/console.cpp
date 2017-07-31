#include <stdio.h>
#include "console.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

#define PADHEX(width, val) setfill('0') << setw(width) << std::hex << uppercase << (unsigned)val


vector<string> split(const char *str, char c = ' ')
{
    vector<string> result;

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        result.push_back(string(begin, str));
    } while (0 != *str++);

    return result;
}


bool startsWith(const string& haystack, const string& needle) {
	return needle.length() <= haystack.length() 
		&& equal(needle.begin(), needle.end(), haystack.begin());
}

void console::handleBreak(vector<string> command_line){

	if (command_line.size() < 2){
		cout << "not enough arguments" << endl;
		return;
	}
	// handle info
	if (command_line[1].compare("info") == 0){
		std::cout << "Breakpoint info:" << endl;
		std::list<UINT16> breakpoints = pZ80CPU->getPCBreakpoints();
     	auto print = [](const int& n) { std::cout << "Breakpoint PC=" << n << "." << std::endl; };
		std::for_each(breakpoints.begin(), breakpoints.end(), print);
		return;
	}
	// handle clear
	if (command_line[1].compare("clear") == 0){
		pZ80CPU->clearPCBreakpoints();
		cout << "breakpoints cleared." << std::endl;
		return;
	}
	// handle add remove
	if (command_line.size() < 3){
		cout << "not enough arguments" << endl;
		return;
	}
	UINT16 addr = 0;

	try{
		if (startsWith(command_line[2],"0x")){
			addr = std::stoi(command_line[2],0,16);
		}
		else{
			addr = std::stoi(command_line[2]);
		}
	}
	catch(...){
		cout << "Invalid PC address\n";
		return;
	}
	if ((addr < 0) || (addr >= 65534)){
		cout << "Invalid PC address\n";
		return;
	}

	if (command_line[1].compare("add") == 0){
		pZ80CPU->addPCBreakpoint(addr);
		cout << "break point PC="<<PADHEX(4,addr)<<" added.\n";
	}
	else if (command_line[1].compare("del") == 0){
		pZ80CPU->delPCBreakpoint(addr);
		cout << "break point PC="<<PADHEX(4,addr)<<" removed.\n";
	}
	pZ80CPUThread->traceMode = true;
	return;
}


void console::handleMemory(vector<string> command_line){

	int count = 40;
	int start_addr = 0;
	if (command_line.size() > 1){
		try{
			if (startsWith(command_line[1],"0x")){
				start_addr = std::stoi(command_line[1],0,16);
			}
			else{
				start_addr = std::stoi(command_line[1]);
			}
		}
		catch(...){
			cout << "Invalid start address\n";
			return;
		}
		if ((start_addr < 0) || (start_addr >= 65534)){
			cout << "Invalid start address\n";
			return;
		}
	}
	if (command_line.size() > 2){
		try{
			count = std::stoi(command_line[2]);
		}
		catch(...){
			cout << "Invalid number, setting default count = 10\n";
			count = 40;
		}
	}
	int i =0;
	for (i = 0;i<count;i++){
		if (i == 0){
			cout << PADHEX(4,start_addr) << ":";
		}
		if (start_addr+i > 65535) break;
		cout << "0x" << PADHEX(2,pZ80Memory->get8(start_addr+i)) << " ";
		if ((i+1) % 10 == 0){
			int j = 0;
			for (j = 0; j < 10; j ++){
				UINT8 chr = pZ80Memory->get8(start_addr+i+j);
				if (isprint(chr)){
					cout << chr;
				}
				else
				{
					cout << ".";
				}
			}
			cout << std::endl;
			// take care about next address in next line
			if (i+1 < count){
				cout << PADHEX(4,start_addr+i+1) << ":";
			}
		}
	}
	cout << std::endl;
}


void console::run() {
	while (true){
		vector<string> command_line;
		string command;
		char *s;
		if (scriptFile->good()){
			std::string line;
			std::getline(*scriptFile,line);
			if (line.length() > 0){
				s = (char *) malloc(line.length() +1);
				sprintf(s, "%s", line.c_str());
				cout << "Executing command: " << line << "len" << line.length() << "." << endl;
			} else
			{
				s= readline("zx#");
				add_history(s);
			}
		}
		else
		{
			s= readline("zx#");
			add_history(s);
		}
		command_line = split(s,' ');
		command = command_line.front();
		free(s);
		if (command.compare("help") == 0){
			cout << "Supported commands" << endl;
			cout << "quit, q - quit program" << endl;
			cout << "step, s - step istruction" << endl;
			cout << "registers, r - dump registers state" << endl;
			cout << "stop - stop CPU execution" << endl;
			cout << "reset - resets CPU" << endl;
			continue;
		}
		if ((command.compare("quit") == 0) ||
				(command.compare("q") == 0)) { 
			cout << "Exit program" << endl;
			pZ80CPU->quit = true;
			pZ80CPUThread->wait();
			pMainWindow->close();
			break;
		}
		else if ((command.compare("step") == 0) ||
			(command.compare("s") == 0))
		{
			pZ80CPUThread->traceMode = true;
			cout << "step instruction" << endl;
			pZ80CPU->executeStep();
			pZ80CPU->getOpcode();
			continue;
		}
		else if ((command.compare("registers") == 0) ||
			(command.compare("r") == 0))
		{
			pZ80CPU->getRegisters().dump();
			continue;
		}
		else if (command.compare("stop") == 0)
		{
			cout << "Execution stopped" << endl;
			pZ80CPUThread->traceMode = true;
			continue;

		}
		else if (command.compare("start") == 0)
		{
			cout << "Execution started" << endl;
			pZ80CPUThread->traceMode = false;
			continue;

		}
		else if ((command.compare("break") == 0) ||
				(command.compare("b") == 0))
		{
			handleBreak(command_line);
		}
		else if ((command.compare("memory") == 0) ||
				(command.compare("m") == 0))
		{
			handleMemory(command_line);
		}
		else if (command.compare("reset") == 0)
		{
			Z80Registers toSet;
			toSet.reset();
			cout << "Reset machine" << endl;
			pZ80CPUThread->traceMode = true;
			pZ80CPU->setRegisters(toSet);
			continue;

		}
		else
		{
			cout << "unknown command " << command << "!" << endl;
		}
	}
}
