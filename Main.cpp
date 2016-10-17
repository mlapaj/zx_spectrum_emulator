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
#include "VIDEO/mainwindow.h"

// QT

#include <QApplication>

/*
 *
 */
using namespace log4cxx;
using namespace log4cxx::xml;
using namespace log4cxx::helpers;
LoggerPtr loggerMyMain(Logger::getLogger( "main"));

int main(int argc, char** argv) {

	const char *ZXSpectrumEmulatorVersion = "0.01";
	DOMConfigurator::configure("Log4cxxConfig.xml");
	LOG4CXX_INFO (loggerMyMain, "Starting ZX Spectrum emulator ver." << ZXSpectrumEmulatorVersion);

    const int ZXSpectrumMemorySize = 65536;
    const char *ZXSpectrumRomName = "48.rom";
    Z80Memory *oZ80Memory;
    oZ80Memory = new Z80Memory(ZXSpectrumMemorySize);
    oZ80Memory->LoadRom(ZXSpectrumRomName);
    Z80CPUModule<Z80Memory> oZ80CPU(oZ80Memory);

	QApplication app(argc, argv);
	MainWindow oMainWindow(oZ80Memory);
	oMainWindow.show();
	return app.exec();

/*
	oZ80CPU.cpuThread();
	oZ80Memory->dump("dump.dat");
*/
    return (EXIT_SUCCESS);

}

