#pragma once

#include <QMainWindow>
#include "Auth_Window.h"

class SidePanel;
class QStackedLayout;
class QWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
   // QWidget* createDashboardWidget();
  //  QWidget* createTasksWidget();
  //  QWidget* createSettingsWidget();

    ~MainWindow()
    {
        
    }
private slots:
    void showDashboard();
    void showTasks();
    void showSettings();

private:

    SidePanel* sidePanel;
    QWidget* mainContentWrapper;
    QStackedLayout* stackedLayout;

    QWidget* topBarWidget;
    QWidget* dashboardWidget;
    QWidget* tasksWidget;
    QWidget* settingsWidget;
};
