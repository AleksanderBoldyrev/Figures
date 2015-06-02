#include <QApplication>
#include "mainwindow.h"
#include "time.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    srand(time(0));
    MainWindow w;
    w.show();
    
    return a.exec();
}
