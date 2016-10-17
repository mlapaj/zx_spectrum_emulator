#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

MainWindow::MainWindow(Z80Memory *memory, QWidget *parent ) :
    QMainWindow(parent)
{
	pixels = new QRgb[zx_width*zx_height];
	memset(pixels,0x00,sizeof(QRgb)*zx_width*zx_height);
	image = new QImage((uchar*)pixels,zx_width,zx_height, QImage::Format_RGB32);
	srand(time(NULL));

	connect( &timer, SIGNAL( timeout() ), SLOT( drawFrame() ) );
	timer.start( 30 );

}

MainWindow::~MainWindow()
{
}



void MainWindow::resizeEvent(QResizeEvent* event)
{
	delete pixels;
	delete image;
	pixels = new QRgb[zx_width*zx_height];
	memset(pixels,0x00,sizeof(QRgb)*zx_width*zx_height);
	image = new QImage((uchar*)pixels,zx_width,zx_height, QImage::Format_RGB32);
}




void MainWindow::paintEvent(QPaintEvent *event){
	painter.begin(this);
	painter.scale(2,2);
	painter.drawImage(0, 0, *image);
	painter.end();
}


void MainWindow::drawFrame(){
	for (int x = 0; x < zx_width; x++){
		for (int y = 0; y < zx_height; y++){
			pixels[x+y*zx_width] = cyan_0;

		}
	}
	update();
}
