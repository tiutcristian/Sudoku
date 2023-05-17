#include "mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <QApplication>
#include <QStyleFactory>
#include <QFile>

void setPalette(QApplication &a)
{
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette p = qApp->palette();

    p.setColor(QPalette::Window, QColor(15,16,18));
    p.setColor(QPalette::Button, QColor(33,36,51));
    p.setColor(QPalette::ButtonText, QColor(107,146,215));
    p.setColor(QPalette::WindowText, QColor(177,178,183));

    a.setPalette(p);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    QApplication a(argc, argv);
    setPalette(a);

    MainWindow w;
    w.show();
    return a.exec();
}
