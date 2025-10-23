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

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(20);
    grid->setContentsMargins(0, 0, 0, 0);

    card_categories_frame = new QFrame;
    card_comments_frame = new QFrame;
    card_tasks_frame = new QFrame;
    
    //==== Categorie Frame =====   
    hrz_card_categories_objects = new QHBoxLayout(card_categories_frame);
    new_categorie_btn = new QPushButton("+ New Categorie");
    new_categorie_btn->setCursor(Qt::PointingHandCursor);

    hrz_card_categories_objects->addWidget(new QLabel("Categories"), 0, Qt::AlignTop);
    hrz_card_categories_objects->addStretch();
    hrz_card_categories_objects->addWidget(new_categorie_btn, 0, Qt::AlignTop);
   
    //==== Comment Frame =====   
    hrz_card_comments_objects = new QHBoxLayout(card_comments_frame);
    new_comment_btn = new QPushButton("+ New Comment");
    new_comment_btn->setCursor(Qt::PointingHandCursor);

    hrz_card_comments_objects->addWidget(new QLabel("Comments"), 0, Qt::AlignTop);
    hrz_card_comments_objects->addStretch();
    hrz_card_comments_objects->addWidget(new_comment_btn, 0, Qt::AlignTop);
    
    //==== Task Frame =====
    hrz_card_tasks_objects = new QHBoxLayout(card_tasks_frame);
    new_task_btn = new QPushButton("+ New Task");
    new_task_btn->setCursor(Qt::PointingHandCursor);

    hrz_card_tasks_objects->addWidget(new QLabel("Tasks"), 0, Qt::AlignTop);
    hrz_card_tasks_objects->addStretch();
    hrz_card_tasks_objects->addWidget(new_task_btn, 0, Qt::AlignTop);

    //==== Add frames to grid layout =====
    grid->addWidget(card_categories_frame, 0, 0);
    grid->addWidget(card_comments_frame, 0, 1);
    grid->addWidget(card_tasks_frame,1,0,1,2);
   
}