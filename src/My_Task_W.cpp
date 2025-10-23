#include "headers/My_Task_W.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

My_Tasks_Widget::My_Tasks_Widget(QWidget* parent) : QWidget(parent)
{
    setStyleSheet(R"(
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

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(20);
    grid->setContentsMargins(0, 0, 0, 0);

    card_categories_frame = new QFrame;
    card_comments_frame = new QFrame;
    card_tasks_frame = new QFrame;

    hrz_card_categories_objects = new QHBoxLayout(card_categories_frame);
    hrz_card_categories_objects->addWidget(new QLabel("Categories"), 0, Qt::AlignTop);
    hrz_card_categories_objects->addStretch();
    hrz_card_categories_objects->addWidget(new QPushButton("+ New Categorie"), 0, Qt::AlignTop);
    
    hrz_card_comments_objects = new QHBoxLayout(card_comments_frame);
    hrz_card_comments_objects->addWidget(new QLabel("Comments"), 0, Qt::AlignTop);
    hrz_card_comments_objects->addStretch();
    hrz_card_comments_objects->addWidget(new QPushButton("+ New Comment"),0, Qt::AlignTop);

    hrz_card_tasks_objects = new QHBoxLayout(card_tasks_frame);
    hrz_card_tasks_objects->addWidget(new QLabel("Tasks"), 0, Qt::AlignTop);
    hrz_card_tasks_objects->addStretch();
    hrz_card_tasks_objects->addWidget(new QPushButton("+ New Task"),0 , Qt::AlignTop);

    grid->addWidget(card_categories_frame, 0, 0);
    grid->addWidget(card_comments_frame, 0, 1);
    grid->addWidget(card_tasks_frame,1,0,1,2);
   
}