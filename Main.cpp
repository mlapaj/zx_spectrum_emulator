/*
 * File:   Main.c
 * Author: lapajmar
 *
 * Created on 18 marzec 2014, 11:20
 */

#include <stdio.h>
#include <stdlib.h>

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include "Z80CPU/Z80CPUModule.hpp"
#include "Z80CPU/Z80CPUModuleThread.hpp"
#include "console/console.hpp"
#include "video/mainwindow.h"

// QT

#include <QApplication>
#include <unistd.h>

/*
 *
 */
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
LoggerPtr loggerMyMain(Logger::getLogger( "main"));

int main(int argc, char** argv) {
	int startTraceMode = 0;
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "th?")) != -1){
		printf("%c\n",c);
		switch (c)
		{
			case 't':
				startTraceMode = 1;
				break;
			case 'h':
			case '?':
				printf("program options:\n");
				printf("-t - start with trace mode\n");
				return 0;
				break;
		}
	}



	const char *ZXSpectrumEmulatorVersion = "0.01";
	DOMConfigurator::configure("Log4cxxConfig.xml");
	LOG4CXX_INFO (loggerMyMain, "Starting ZX Spectrum emulator ver." << ZXSpectrumEmulatorVersion);

    const int ZXSpectrumMemorySize = 65536;
    const char *ZXSpectrumRomName = "48.rom";
    Z80Memory *oZ80Memory;
    oZ80Memory = new Z80Memory(ZXSpectrumMemorySize);
    oZ80Memory->LoadRom(ZXSpectrumRomName);
    Z80CPUModule<Z80Memory> oZ80CPU(oZ80Memory);
	Z80CPUModuleThread oZ80CPUThread;
	if (startTraceMode){
		oZ80CPUThread.traceMode = true;
	}
	oZ80CPUThread.pZ80CPU = &oZ80CPU;



	/*oZ80Memory->load("test.scr",0x4000,0x1B00);*/
	oZ80Memory->dump("dump.dat"); 
	QApplication app(argc, argv);
	MainWindow oMainWindow(oZ80Memory);

    console oConsole;
	oConsole.pMainWindow = &oMainWindow;
	oConsole.pZ80CPU = &oZ80CPU;
	oConsole.pZ80CPUThread = &oZ80CPUThread;
	oConsole.pZ80Memory = oZ80Memory;
	oZ80CPUThread.start();
	oConsole.start();
	oMainWindow.show();
	return app.exec();



    return (EXIT_SUCCESS);

}

