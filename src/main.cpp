#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QStyleFactory>
#include "headers/ApplicationController.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     QApplication::setStyle(QStyleFactory::create("WindowsVista"));

     ApplicationController window;

    return app.exec();
}
