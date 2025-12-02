#include "headers/SidePanel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QCoreApplication>


SidePanel::SidePanel(QWidget* parent)
    : QWidget(parent)
{
    setStyleSheet(R"(
        QWidget {
            background-color: #ffffff;
            border-radius: 20px;
        }
        QPushButton {
            border: none;
            text-align: center;
            padding: 10px 20px;
            font-size: 15px;
            color: #444;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 20, 10, 20);
    layout->setSpacing(10);

    //dashboard = new QPushButton("📊 Dashboard");
    myTasks = new QPushButton("🗒️ My Tasks");
    settings = new QPushButton("⚙️ Settings");
    logOut = new QPushButton("🚪 Log out");

    //layout->addWidget(dashboard);
    layout->addWidget(myTasks);
    layout->addStretch();
    layout->addWidget(settings);
    layout->addWidget(logOut);

    //connect(dashboard, &QPushButton::clicked, this, &SidePanel::dashboardClicked);
    connect(myTasks, &QPushButton::clicked, this, &SidePanel::tasksClicked);
    connect(settings, &QPushButton::clicked, this, &SidePanel::settingsClicked);
    connect(logOut, &QPushButton::clicked, qApp, &QCoreApplication::exit);
}
