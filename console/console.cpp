#include <stdio.h>
#include "console.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;


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


void console::run() {
	while (true){
		vector<string> command_line;
		string command;
		char *s;
		s= readline("zx#");
		add_history(s);
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
		else if ((command.compare("stop") == 0) ||
				(command.compare("st") == 0))
		{
			cout << "Execution stopped" << endl;
			pZ80CPUThread->traceMode = true;
			continue;

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
