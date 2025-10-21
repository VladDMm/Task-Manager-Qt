#include "headers/SidePanel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QCoreApplication>

//SidePanel::SidePanel(QWidget *parent) : QWidget(parent)
//{
//	//dashboard = new QPushButton("Dashboard", this);
//	//my_tasks = new QPushButton("My tasks", this);
//	//settings = new QPushButton("Settings", this);
//	//log_out = new QPushButton("Log out", this);
//
//
//	//QFrame* side_frame = new QFrame(this);
//	//QVBoxLayout* v_frame_layout = new QVBoxLayout;
//	//v_frame_layout->addWidget(dashboard);
//	//v_frame_layout->addWidget(my_tasks);
//	//v_frame_layout->addWidget(settings);
//	//v_frame_layout->addWidget(log_out);
//	//v_frame_layout->setSpacing(10);
//
//
//	//side_frame->setLayout(v_frame_layout);
//
//	dashboard = new QPushButton("Dashboard", this);
//	myTasks = new QPushButton("My Tasks", this);
//	settings = new QPushButton("Settings", this);
//	logOut = new QPushButton("Log Out", this);
//
//	QVBoxLayout* layout = new QVBoxLayout;
//	layout->addWidget(dashboard);
//	layout->addWidget(myTasks);
//	layout->addWidget(settings);
//	layout->addWidget(logOut);
//	layout->addStretch(); // împinge butoanele sus
//
//	setLayout(layout);
//	setStyleSheet("background-color: #f0f0f0;"); // gri deschis pentru panel
//}

//SidePanel::SidePanel(QWidget* parent) : QWidget(parent)
//{
//    dashboard = new QPushButton("Dashboard", this);
//    myTasks = new QPushButton("My Tasks", this);
//    settings = new QPushButton("Settings", this);
//    logOut = new QPushButton("Log Out", this);
//
//    QVBoxLayout* layout = new QVBoxLayout;
//    layout->addWidget(dashboard);
//    layout->addWidget(myTasks);
//    layout->addWidget(settings);
//    layout->addWidget(logOut);
//    layout->addStretch();
//
//    setLayout(layout);
//    setStyleSheet("background-color: #e0e0e0;");
//
//    connect(dashboard, &QPushButton::clicked, this, &SidePanel::dashboardClicked);
//    connect(myTasks, &QPushButton::clicked, this, &SidePanel::tasksClicked);
//    connect(settings, &QPushButton::clicked, this, &SidePanel::settingsClicked);
//    connect(logOut, &QPushButton::clicked, this, &SidePanel::logOutClicked);
//}

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

    dashboard = new QPushButton("📊 Dashboard");
    myTasks = new QPushButton("🗒️ My Tasks");
    settings = new QPushButton("⚙️ Settings");
    logOut = new QPushButton("🚪 Log out");

    layout->addWidget(dashboard);
    layout->addWidget(myTasks);
    layout->addStretch();
    layout->addWidget(settings);
    layout->addWidget(logOut);

    connect(dashboard, &QPushButton::clicked, this, &SidePanel::dashboardClicked);
    connect(myTasks, &QPushButton::clicked, this, &SidePanel::tasksClicked);
    connect(settings, &QPushButton::clicked, this, &SidePanel::settingsClicked);
    connect(logOut, &QPushButton::clicked, qApp, &QCoreApplication::exit);
}
