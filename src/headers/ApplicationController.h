#pragma once
#include <QObject>

#include "AuthWindow.h"
#include "RegWindow.h"
#include "MainWindow.h"

class ApplicationController : public QObject
{
    Q_OBJECT

private:
    Auth_Window* authWindow;
    Reg_Window* regWindow;
    MainWindow* mainWindow;

public:
    ApplicationController();

private slots:
    void showAuthWindow();
    void showRegWindow();
    void showMainWindow();
    void authentificate();

};
