#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QObject>
#include <vector>
#include <complex>
#include <functional>
#include "../Z80CPU/Z80Memory.hpp"
using namespace std;

namespace Ui {
class MainWindow;
}

const int zx_width = 256;
const int zx_height = 192;

const long black_0 =    0x000000;
const long black_1 =    0x000000;
const long blue_0 =     0x0000D7;
const long blue_1 =     0x0000FF;
const long red_0 =      0xD70000;
const long red_1 =      0xFF0000;
const long magneta_0 =  0xD700D7;
const long  magneta_1 =  0xFF00FF;
const long green_0 =    0x00D700;
const long green_1 =    0x00FF00;
const long cyan_0 =     0x00D7D7;
const long cyan_1 =     0x00FFFF;
const long yellow_0 =   0xD7D700;
const long yellow_1 =   0xFFFF00;
const long white_0 =    0xD7D7D7;
const long white_1 =    0xFFFFFF;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Z80Memory *memory, QWidget *parent = 0);
    ~MainWindow();
protected:
	QPainter painter;
	QTimer timer;
	Z80Memory *videoMemory;
    QRgb *pixels;
	QImage *image;
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

private:
public slots:
	void drawFrame();
};

#endif // MAINWINDOW_H
