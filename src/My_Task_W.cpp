#include "headers/My_Task_W.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>

My_Tasks_Widget::My_Tasks_Widget(QWidget* parent) : QWidget(parent)
{
	/*card = new QFrame(this);
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
    layout->addWidget(new QLabel("Tasks"));
    layout->addStretch();

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(20);
    grid->setContentsMargins(0, 0, 0, 0);

    grid->addWidget(card, 0, 0);*/

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


    grid->addWidget(makeCard("Categories"), 0, 0);
    grid->addWidget(makeCard("Comments"), 0, 1);
    grid->addWidget(makeCard("Tasks"),1,0,1,2);
}