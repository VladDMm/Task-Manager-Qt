#pragma once

#include <QMainWindow>
#include "AuthWindow.h"

class SidePanel;
class QStackedLayout;
class QWidget;
class TopBarWidget;
//class DashboardWidget;
class MyTasksWidget;
class SettingsWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    SidePanel*       sidePanel;
    QWidget*         mainContentWrapper;
    QStackedLayout*  stackedLayout;
    TopBarWidget*    topBarWidget;
    //DashboardWidget* dashboardWidget;
    MyTasksWidget*   tasksWidget;
    SettingsWidget*  settingsWidget;

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    //void showDashboard();

    void showTasks();
    void showSettings();
public:
   // void refreshTasks();
    void initializing_components();
};
