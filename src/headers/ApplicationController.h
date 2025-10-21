#pragma once
#include <QObject>

#include "Auth_Window.h"
#include "Reg_Window.h"
#include "MainWindow.h"

class ApplicationController : public QObject
{
    Q_OBJECT
public:
    ApplicationController();

private slots:
    void showAuthWindow();
    void showRegWindow();
    void showMainWindow();
    void authentificate();

private:
    Auth_Window* authWindow;
    Reg_Window* regWindow;
    MainWindow* mainWindow;
};
