#include "QTools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTools w;
    w.show();

    return a.exec();
}
