/*
 * name		: Seungjae Yoo
 * email	: sjyoo@postech.ac.kr
 * date		: 2017.12.03
 */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	// for random numbers
    srand(time(NULL));
	
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
