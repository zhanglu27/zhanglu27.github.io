#include "widget.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    if(QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    login l;
    l.show();
    return a.exec();
}
