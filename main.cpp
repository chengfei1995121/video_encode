#include "mainwindow.h"
#include <QApplication>
#include "stb_implement.h"
#include "encode.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
