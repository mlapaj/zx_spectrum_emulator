#ifndef CONSOLE_H
#define	CONSOLE_H

#include <QThread>
#include <iostream>
#include <fstream>
#include "../Z80CPU/Z80CPUModule.hpp"
#include "../Z80CPU/Z80CPUModuleThread.hpp"
#include "../video/mainwindow.h"


class console : public QThread {
Q_OBJECT
public:
    void run();
	MainWindow *pMainWindow;
    Z80CPUModule<Z80Memory> *pZ80CPU;
	Z80Memory *pZ80Memory;
	Z80CPUModuleThread *pZ80CPUThread;
	std::ifstream *scriptFile;

private:
	void handleBreak(vector<string> command_line);
    void handleMemory(vector<string> command_line);
};

#endif
