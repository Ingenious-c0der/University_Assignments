#include "qtdemonstration.h"

#include <QApplication>
#include <QLabel>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDemonstration w;
    w.show();
    return a.exec();
}
