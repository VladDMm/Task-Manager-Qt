#include "headers/Top_Bar_W.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
#include <QToolButton>
#include <QIcon>
#include <QPixmap>
#include <QApplication>

Top_Bar_Widget::Top_Bar_Widget(QWidget* parent)
    : QWidget(parent)
{
    card = new QFrame(this);
    card->setStyleSheet(R"(
        QFrame {
            background-color: #ffffff;
            border-radius: 15px;
            border: 1px solid #e5e5e5;
        }
        QLabel {
            font-size: 16px;
            font-weight: bold;
            color: #333;
        }
        QPushButton, QToolButton {
            border: none;
            background: transparent;
        }
    )");


    cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(20, 10, 20, 10);
    cardLayout->setSpacing(15);

    // === Search Bar ===
   /* QLineEdit* search = new QLineEdit;
    search->setPlaceholderText("Search...");
    search->setFixedWidth(250);
    search->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid #ddd;
            border-radius: 10px;
            padding: 6px 12px;
            background-color: #fafafa;
        }
        QLineEdit:focus {
            border-color: #4a90e2;
            background-color: #fff;
        }
    )");*/

    // === Buton “New Task” ===
    newTask = new QPushButton("+ New Task");
    newTask->setCursor(Qt::PointingHandCursor);
    newTask->setStyleSheet(R"(
        QPushButton {
            background-color: #4a90e2;
            color: white;
            border-radius: 10px;
            padding: 6px 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #3c7cd4;
        }
    )");

    
    /*notifButton = new QToolButton;
    notifButton->setIcon(QIcon(":/rsc/notification.png"));
    notifButton->setText("🔔");
    notifButton->setIconSize(QSize(24, 24));
    notifButton->setToolTip("Notifications");
    notifButton->setCursor(Qt::PointingHandCursor);*/
 
    profileButton = new QToolButton;
    profileButton->setIcon(QIcon(":/rsc/user.png"));
    profileButton->setText("👤");
    profileButton->setIconSize(QSize(28, 28));
    profileButton->setToolTip("Profile");
    profileButton->setCursor(Qt::PointingHandCursor);
    profileButton->setPopupMode(QToolButton::InstantPopup);
    profileButton->setStyleSheet(R"(
        QToolButton {
            border-radius: 14px;
            padding: 2px;
        }
        QToolButton:hover {
            background-color: #f2f2f2;
        }
    )");

    QMenu* profileMenu = new QMenu(profileButton);
    profileMenu->setStyleSheet(R"(
        QMenu {
            background-color: #ffffff;
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            padding: 6px;
        }
        QMenu::item {
            padding: 6px 16px;
            border-radius: 6px;
        }
        QMenu::item:selected {
            background-color: #4a90e2;
            color: white;
        }
    )");

    QAction* actProfile = new QAction("Profile", profileMenu);
    QAction* actSettings = new QAction("Settings", profileMenu);
    QAction* actLogout = new QAction("Logout", profileMenu);

    profileMenu->addAction(actProfile);
    profileMenu->addAction(actSettings);
    profileMenu->addSeparator();
    profileMenu->addAction(actLogout);

    profileButton->setMenu(profileMenu);

    cardLayout->addStretch();
    //cardLayout->addWidget(search);
    cardLayout->addSpacing(10);
    cardLayout->addWidget(newTask);
    cardLayout->addSpacing(10);
    //cardLayout->addWidget(notifButton);
    cardLayout->addWidget(profileButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(card);

    // === Connects ===
    connect(actProfile, &QAction::triggered, this, [] {
        qDebug("Profile clicked");
        });
    connect(actSettings, &QAction::triggered, this, [] {
        qDebug("Settings clicked");
        });
    connect(actLogout, &QAction::triggered, qApp, QApplication::quit);
}
