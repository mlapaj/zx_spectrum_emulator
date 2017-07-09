#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
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
const QRgb zx_col_0[8] =
{
	0x000000,
	0x0000D7,
	0xD70000,
	0xD700D7,
	0x00D700,
	0x00D7D7,
	0xD7D700,
	0xD7D7D7
};

const long colorData =  0x4000;
const long attribData = 0x5800;

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
