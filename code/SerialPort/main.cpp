#include "serial.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serial w;
    w.resize(100, 480);
    w.show();
    return a.exec();
}
