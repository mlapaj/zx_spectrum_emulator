#ifndef Z80CPUMODULETHREAD_H
#define	Z80CPUMODULETHREAD_H

#include <QThread>

#include "../Z80CPU/Z80CPUModule.hpp"
#include "../video/mainwindow.h"


class Z80CPUModuleThread : public QThread {
public:
	Z80CPUModuleThread();
    void run();
    Z80CPUModule<Z80Memory> *pZ80CPU;
private:
    LoggerPtr logger;
};

#endif
