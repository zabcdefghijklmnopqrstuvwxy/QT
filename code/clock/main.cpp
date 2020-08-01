#include "digiclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    digiclock w;
    w.show();
    return a.exec();
}
