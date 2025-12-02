#pragma once

#include <QWidget>

class QPushButton;

class SidePanel : public QWidget
{
    Q_OBJECT

private:
    //QPushButton* dashboard;
    QPushButton* myTasks;
    QPushButton* settings;
    QPushButton* logOut;

public:
    SidePanel(QWidget* parent = nullptr);

signals:
    //void dashboardClicked();
    void tasksClicked();
    void settingsClicked();


};
