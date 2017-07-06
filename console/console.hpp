#ifndef CONSOLE_H
#define	CONSOLE_H

#include <QThread>
class console : public QThread {
Q_OBJECT
public:
    void run();
};

#endif
