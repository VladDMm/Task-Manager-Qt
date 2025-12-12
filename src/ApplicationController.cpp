#include "headers/ApplicationController.h"
#include "headers/MainWindow.h"
#include <QMessageBox>
#include "headers/TaskManagerService.h"

User current_user;

ApplicationController::ApplicationController()
{
    mainWindow = new MainWindow;
    authWindow = new AuthWindow;
    regWindow = new RegWindow;
    
    connect(authWindow, &AuthWindow::register_button_ath_win_clicked,
        this, &ApplicationController::showRegWindow);

    connect(authWindow, &AuthWindow::login_button_clicked,
        this, &ApplicationController::authentificate);

    connect(regWindow, &RegWindow::back_auth_button_reg_win_clicked, this, &ApplicationController::showAuthWindow);
    
    // show initial authentification window
    authWindow->show();
}

void ApplicationController::showAuthWindow()
{
    regWindow->hide();
    authWindow->show();
}

void ApplicationController::showRegWindow()
{
    try
    {
        authWindow->hide();
        regWindow->show();
    }
    catch (const std::runtime_error& e)
    {
        QMessageBox::warning(regWindow, "Registration failed", e.what());
        regWindow->show();
    }
}

void ApplicationController::authentificate()
{
    QString username = authWindow->getLogin();
    QString password = authWindow->getPass();

    try
    {
        if (username.isEmpty() || password.isEmpty())
        {
            throw std::runtime_error("Empty credentials");
        }

        current_user = db_service->get_user(username.toStdString(), password.toStdString());
        showMainWindow();
    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(authWindow, "Login failed", "Invalid credentials!");
        authWindow->show();
    }
}

void ApplicationController::showMainWindow()
{
    authWindow->close();
    regWindow->close();
    taskService_.initializing_data();
    mainWindow->initializing_components();
    mainWindow->show();   
}