#include "headers/DashboardW.h"

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>

Dashboard_Widget::Dashboard_Widget(QWidget* parent) : QWidget(parent)
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
                margin: 10px;
            }
        )");

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(20);
    grid->setContentsMargins(0, 0, 0, 0);
    
    auto makeCard = [](const QString& title) {
        QFrame* card = new QFrame;
        card->setStyleSheet(R"(
            QFrame {
                background-color: #ffffff;
                border-radius: 15px;
                border: 1px solid #e5e5e5;
            }
            QLabel {
                font-size: 16px;
                font-weight: bold;
                margin: 10px;
                border: none;
            }
        )");
        QVBoxLayout* layout = new QVBoxLayout(card);
        layout->addWidget(new QLabel(title));
        layout->addStretch();
        return card;
        };


    grid->addWidget(makeCard("Calendar"), 0, 0);
    grid->addWidget(makeCard("My Tasks"), 0, 1);
    grid->addWidget(makeCard("Comments"), 1, 0);
    grid->addWidget(makeCard("Categories"), 1, 1);
    //grid->addWidget(makeCard("Tracking"), 1, 1);
}
