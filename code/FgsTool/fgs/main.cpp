#include "fgs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    fgs w;
    w.show();

    return a.exec();
}
