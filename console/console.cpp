#include <stdio.h>
#include "console.hpp"
#include <iostream>
#include <string>
#include <vector>

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
		string s;
		cout << "zx#";
		getline(cin,s);
		command_line = split(s.c_str(),' ');
		command = command_line.front();
		if (command.compare("quit") == 0) { 
			cout << "Exit program" << endl;
			pZ80CPU->quit = true;
			pZ80CPUThread->wait();
			pMainWindow->close();
			break;
		}
		else
		{
			cout << "unknown command " << command << "!" << endl;
		}
	}
}
