#include "Z80CPUModuleThread.hpp"
Z80CPUModuleThread::Z80CPUModuleThread(): QThread(),
	logger(Logger::getLogger("Z80Module")) {
    LOG4CXX_DEBUG(logger, "class created");
	traceMode = false;
}

void Z80CPUModuleThread::run() {
	LOG4CXX_DEBUG(logger, "thread started");
	while (true){
		if (traceMode){
			QThread::yieldCurrentThread();
		}
		if (pZ80CPU->quit == true) { 
			break;
		}
		pZ80CPU->executeStep();
	}
	LOG4CXX_DEBUG(logger, "thread end");
}
