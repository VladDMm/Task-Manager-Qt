#include "headers/MainWindow.h"
#include "headers/SidePanel.h"
#include "headers/MySQLConnector.h"
#include "headers/CentralDatabaseClass.h"
#include "headers/My_Task_W.h"
#include"headers/Settings_W.h"
#include"headers/Dashboard_W.h"
#include"headers/Top_Bar_W.h"


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

//MainWindow::MainWindow(QWidget* parent) :
//	QMainWindow(parent)
//{
//    /*QPixmap newpix("new.png");
//    QPixmap openpix("open.png");
//    QPixmap quitpix("quit.png");
//
//    QAction* quit;
//    QMenu* file;
//
//    file = menuBar()->addMenu("&File");
//    quit = file->addAction(QIcon(quitpix), "Quit");
//    
//    quit->setShortcut(tr("CTRL+Q"));
//    connect(quit, &QAction::triggered, qApp, &QCoreApplication::quit);
//
//    QToolBar* toolbar = addToolBar("main toolbar");
//    toolbar->addAction(QIcon(newpix), "New File");
//    toolbar->addAction(QIcon(openpix), "Open File");
//    toolbar->addSeparator();
//
//    toolbar->addAction(quit);
//    connect(quit, &QAction::triggered, qApp, &QCoreApplication::quit);   */
//
//    QWidget* centralWidget = new QWidget(this);
//    QHBoxLayout* mainLayout = new QHBoxLayout;
//
//    sidePanel = new SidePanel;
//    sidePanel->setFixedWidth(100); // lățime fixă pentru panelul lateral
//
//    mainContentArea = new QWidget;
//    mainContentArea->setStyleSheet("background-color: white;");
//    mainContentArea->setObjectName("mainContentArea");
//
//    // Poți seta layout aici dacă vrei să adaugi widgeturi dinamice ulterior
//    QVBoxLayout* contentLayout = new QVBoxLayout;
//    mainContentArea->setLayout(contentLayout);
//
//    mainLayout->addWidget(sidePanel);
//    mainLayout->addWidget(mainContentArea, 1); // extinde pe restul spațiului
//
//    centralWidget->setLayout(mainLayout);
//    setCentralWidget(centralWidget);
//
//  /*  QVBoxLayout* vbox = new QVBoxLayout(central);
//    QHBoxLayout* hbox = new QHBoxLayout();
//    QTextEdit* edit = new QTextEdit(central);
//
//    QPushButton *okBtn = new QPushButton("OK", central);
//    QPushButton *applyBtn = new QPushButton("Apply", central);
//
//    hbox->addWidget(okBtn, 1, Qt::AlignRight);
//    hbox->addWidget(applyBtn, 0);
//    vbox->addWidget(edit);
//    hbox->addStretch();
//    vbox->addLayout(hbox);
//
//    statusBar()->showMessage("Ready");
//    setCentralWidget(central);*/
//}


//MainWindow::MainWindow(QWidget* parent)
//    : QMainWindow(parent)
//{
//    QWidget* centralWidget = new QWidget(this);
//    QHBoxLayout* mainLayout = new QHBoxLayout;
//
//    // SidePanel
//    sidePanel = new SidePanel;
//    sidePanel->setFixedWidth(150);
//
//    // Main area cu fundal alb
//    mainContentWrapper = new QWidget;
//    mainContentWrapper->setStyleSheet("background-color: white;");
//
//    // Layout pentru a "pune peste" diverse widgeturi
//    stackedLayout = new QStackedLayout;
//
//    // Exemplu de widgeturi
//    dashboardWidget = new QLabel("Dashboard"); // poți înlocui cu o clasă proprie
//    dashboardWidget->setStyleSheet("background-color: lightblue; font-size: 20px;");
//
//    tasksWidget = new QLabel("Tasks");
//    tasksWidget->setStyleSheet("background-color: lightgreen; font-size: 20px;");
//
//    settingsWidget = new QLabel("Settings");
//    settingsWidget->setStyleSheet("background-color: lightcoral; font-size: 20px;");
//
//    // Adăugăm widgeturile în stacked layout
//    stackedLayout->addWidget(dashboardWidget);
//    stackedLayout->addWidget(tasksWidget);
//    stackedLayout->addWidget(settingsWidget);
//
//    mainContentWrapper->setLayout(stackedLayout);
//
//    // Final layout setup
//    mainLayout->addWidget(sidePanel);
//    mainLayout->addWidget(mainContentWrapper, 1);
//
//    centralWidget->setLayout(mainLayout);
//    setCentralWidget(centralWidget);
//
//    
//    connect(sidePanel, &SidePanel::dashboardClicked, this, &MainWindow::showDashboard);
//    connect(sidePanel, &SidePanel::tasksClicked, this, &MainWindow::showTasks);
//    connect(sidePanel, &SidePanel::settingsClicked, this, &MainWindow::showSettings);
//}
//
//void MainWindow::showDashboard() {
//    stackedLayout->setCurrentWidget(dashboardWidget);
//}
//
//void MainWindow::showTasks() {
//    stackedLayout->setCurrentWidget(tasksWidget);
//}
//
//void MainWindow::showSettings() {
//    stackedLayout->setCurrentWidget(settingsWidget);
//}

MySQLConnector my_sql;
MySQLService msql_srv(my_sql.get_connection());
Database db(msql_srv);

auto& task_srv = TaskService::get_instance();

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
    topBarWidget = new Top_Bar_Widget(this);
    dashboardWidget = new Dashboard_Widget(this);
    tasksWidget = new My_Tasks_Widget(this);
    settingsWidget = new Settings_Widget(this);

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
    connect(sidePanel, &SidePanel::settingsClicked, this, &MainWindow::showSettings);
    
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
