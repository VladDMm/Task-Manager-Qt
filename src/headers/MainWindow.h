#pragma once

#include <QMainWindow>
#include "Auth_Window.h"

class SidePanel;
class QStackedLayout;
class QWidget;
class Top_Bar_Widget;
class Dashboard_Widget;
class My_Tasks_Widget;
class Settings_Widget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SidePanel* sidePanel;
    QWidget* mainContentWrapper;
    QStackedLayout* stackedLayout;
    Top_Bar_Widget* topBarWidget;
    Dashboard_Widget* dashboardWidget;
    My_Tasks_Widget* tasksWidget;
    Settings_Widget* settingsWidget;

public:
    MainWindow(QWidget* parent = nullptr);

    ~MainWindow()
    {
        
    }
private slots:
    void showDashboard();
    void showTasks();
    void showSettings();
};
