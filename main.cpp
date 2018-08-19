#include "QTools.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *parent = new QWidget;
    QTools *w = new QTools(parent);
    w->show();

    int ret = a.exec();
    delete parent;
    return ret;
}
