#include "headers/MainWindow.h"
#include "headers/SidePanel.h"
#include "headers/MySQLConnector.h"
#include "headers/CentralDatabaseClass.h"
#include "headers/MyTaskW.h"
#include "headers/SettingsW.h"
#include "headers/DashboardW.h"
#include "headers/TopBarW.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QToolBar>
#include <QIcon>

#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QPushButton>
#include <QCoreApplication>


MySQLConnector my_sql;
MySQLService msql_srv_(my_sql.get_connection());
Database db(msql_srv_);

TaskService taskService_;


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    setWindowTitle("Task Manager");
    setWindowIcon(QIcon(":/rsc/web.png"));

    central->setStyleSheet("background-color: #f8f5ee;");

    QHBoxLayout* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);

    // === Side Panel ===
    sidePanel = new SidePanel(this);
    sidePanel->setFixedWidth(200);

    // === Main Content ===
    mainContentWrapper = new QWidget;
    mainContentWrapper->setStyleSheet("background: transparent;");

    stackedLayout = new QStackedLayout(mainContentWrapper);

    // widgets
    topBarWidget = new TopBarWidget(this);
    dashboardWidget = new DashboardWidget(this);
    tasksWidget = new MyTasksWidget(this);
    settingsWidget = new SettingsWidget(this);

    stackedLayout->addWidget(dashboardWidget);
    stackedLayout->addWidget(tasksWidget);
    stackedLayout->addWidget(settingsWidget);

    // === Container for right content ===
    
    QWidget* rightContainer = new QWidget;
    QVBoxLayout* rightLayout = new QVBoxLayout(rightContainer);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(15); // distance top bar and content

    rightLayout->addWidget(topBarWidget);
    rightLayout->addWidget(mainContentWrapper, 1);

    mainLayout->addWidget(sidePanel);
    mainLayout->addWidget(rightContainer, 1);

    // === Connects ===
    connect(sidePanel, &SidePanel::dashboardClicked, this, &MainWindow::showDashboard);
    connect(sidePanel, &SidePanel::tasksClicked, this, &MainWindow::showTasks);
    //connect(sidePanel, &SidePanel::tasksClicked, topBarWidget, &TopBarWidget::show_buttons_in_top_bar);
    //connect(sidePanel, &SidePanel::dashboardClicked, topBarWidget, &TopBarWidget::clear_top_bar_buttons);
    //connect(sidePanel, &SidePanel::settingsClicked, topBarWidget, &TopBarWidget::clear_top_bar_buttons);
    connect(sidePanel, &SidePanel::settingsClicked, this, &MainWindow::showSettings);
    connect(sidePanel, &SidePanel::tasksClicked, tasksWidget, &MyTasksWidget::refresh_task_list);
    connect(sidePanel, &SidePanel::tasksClicked, tasksWidget, &MyTasksWidget::refresh_category_list);
    connect(sidePanel, &SidePanel::tasksClicked, tasksWidget, &MyTasksWidget::refresh_comment_list);
}


void MainWindow::showDashboard() {
    stackedLayout->setCurrentWidget(dashboardWidget);
}

void MainWindow::showTasks() {
    stackedLayout->setCurrentWidget(tasksWidget);
}

void MainWindow::showSettings() {
    stackedLayout->setCurrentWidget(settingsWidget);
}

//void MainWindow::refreshTasks() {
//    tasksWidget->refresh_task_list();
//}

//
//QWidget* MainWindow::createDashboardWidget()
//{
//    QWidget* page = new QWidget;
//    QGridLayout* grid = new QGridLayout(page);
//    grid->setSpacing(20);
//    grid->setContentsMargins(0, 0, 0, 0);
//
//    auto makeCard = [](const QString& title) {
//        QFrame* card = new QFrame;
//        card->setStyleSheet(R"(
//            QFrame {
//                background-color: #ffffff;
//                border-radius: 15px;
//                border: 1px solid #e5e5e5;
//            }
//            QLabel {
//                font-size: 16px;
//                font-weight: bold;
//                margin: 10px;
//            }
//        )");
//        QVBoxLayout* layout = new QVBoxLayout(card);
//        layout->addWidget(new QLabel(title));
//        layout->addStretch();
//        return card;
//        };
//
//    grid->addWidget(makeCard("Calendar"), 0, 0);
//    grid->addWidget(makeCard("My Tasks"), 0, 1);
//    grid->addWidget(makeCard("Comments"), 0, 2);
//    grid->addWidget(makeCard("Categories"), 1, 0);
//    grid->addWidget(makeCard("Tracking"), 1, 1);
//
//    return page;
//}
//
//QWidget* MainWindow::createTasksWidget()
//{
//    QWidget* page = new QWidget;
//    QGridLayout* grid = new QGridLayout(page);
//    grid->setSpacing(20);
//    grid->setContentsMargins(0, 0, 0, 0);
//
//    auto makeCard = [](const QString& title) {
//        QFrame* card = new QFrame;
//        card->setStyleSheet(R"(
//            QFrame {
//                background-color: #ffffff;
//                border-radius: 15px;
//                border: 1px solid #e5e5e5;
//            }
//            QLabel {
//                font-size: 16px;
//                font-weight: bold;
//                margin: 10px;
//            }
//        )");
//        QVBoxLayout* layout = new QVBoxLayout(card);
//        layout->addWidget(new QLabel(title));
//        layout->addStretch();
//        return card;
//        };
//
//    grid->addWidget(makeCard("Calendar"), 0, 0);
//   // grid->addWidget(makeCard("My Tasks"), 0, 1);
// //   grid->addWidget(makeCard("Comments"), 0, 2);
// //   grid->addWidget(makeCard("Categories"), 1, 0);
// //   grid->addWidget(makeCard("Tracking"), 1, 1);
//
//    return page;
//}
//
//QWidget* MainWindow::createSettingsWidget()
//{
//    QWidget* page = new QWidget;
//    QGridLayout* grid = new QGridLayout(page);
//    grid->setSpacing(20);
//    grid->setContentsMargins(0, 0, 0, 0);
//
//    auto makeCard = [](const QString& title) {
//        QFrame* card = new QFrame;
//        card->setStyleSheet(R"(
//            QFrame {
//                background-color: #ffffff;
//                border-radius: 15px;
//                border: 1px solid #e5e5e5;
//            }
//            QLabel {
//                font-size: 16px;
//                font-weight: bold;
//                margin: 10px;
//            }
//        )");
//        QVBoxLayout* layout = new QVBoxLayout(card);
//        layout->addWidget(new QLabel(title));
//        layout->addStretch();
//        return card;
//        };
//
//    grid->addWidget(makeCard("Calendar"), 0, 0);
//    grid->addWidget(makeCard("My Tasks"), 0, 1);
// //   grid->addWidget(makeCard("Comments"), 0, 2);
// //   grid->addWidget(makeCard("Categories"), 1, 0);
// //   grid->addWidget(makeCard("Tracking"), 1, 1);
//
//    return page;
//}
