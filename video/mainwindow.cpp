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
	videoMemory = memory;
	pixels = new QRgb[zx_width*zx_height];
	memset(pixels,0x00,sizeof(QRgb)*zx_width*zx_height);
	image = new QImage((uchar*)pixels,zx_width,zx_height, QImage::Format_RGB32);
	srand(time(NULL));

	connect( &timer, SIGNAL( timeout() ), SLOT( drawFrame() ) );
	timer.start( 30 );
	this->setFixedSize(zx_width*2,zx_height*2);

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
	/* zx spectrum has video memory at 0x4000 location
	 * attributes at 0x5800 location.
	 * Video memory location is divided for three parts
	 * first part contains lines 0-64, second 64-128, 128-256
	 * one line = 32 bytes. 
	 * First part is constructed in this way (256 bytes):
	 * 1st 32 bytes for 0 line
	 * 2nd 32 bytes for 8 line
	 * 3nd 32 bytes for 16 line
	 * ....
	 * 32nd 32 bytes for 1 line
	 * 9, 17, 25, 33, 41, 49, 57
	 * at 0x5800 we have attrib area, one byte is for 8x8 atea
	 * same as SCR format. See details:
	 * http://www.zx-modules.de/fileformats/scrformat.html
	 * */
	int offset = 0;
	for (int third = 0; third < 3; third++)
	{
		for (int pixLineBlock = 0; pixLineBlock < 8; pixLineBlock++)
		{
			for (int curLine=0+pixLineBlock;curLine<64;curLine+=8)
			{
				for (int curCol=0;curCol<32;curCol++)
				{
					UINT8 attrib = videoMemory->get8(attribData + ((third*64+curLine)/8)*32 + curCol);
					UINT8 ink = attrib & 0x7;
					UINT8 pap = attrib >> 3 & 7;
					UINT8 color = videoMemory->get8(colorData+offset++);
					for (int curChar=0;curChar<8;curChar++){
						if ((color >> (7-curChar)) & 0x1){
							QRgb color_rgb = zx_col_0[ink];
							pixels[(zx_width*64*third)+(curLine*zx_width)+(curCol*8)+curChar] = color_rgb;
						}
						else
						{
							QRgb color_rgb = zx_col_0[pap];
							pixels[(zx_width*64*third)+(curLine*zx_width)+(curCol*8)+curChar] = color_rgb;
						}
					}
				}
			}
		}
	}
	update();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        cout << "esc pressed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
		cout << "esc released!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }
}

