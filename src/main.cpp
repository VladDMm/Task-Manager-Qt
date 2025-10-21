#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include "headers/ApplicationController.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
    
     ApplicationController window;

    return app.exec();
}
