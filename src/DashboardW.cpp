#include "headers/DashboardW.h"

#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QListWidget>

DashboardWidget::DashboardWidget(QWidget* parent) : QWidget(parent)
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

    //QGridLayout* grid = new QGridLayout(this);
    //grid->setSpacing(20);
    //grid->setContentsMargins(0, 0, 0, 0);
    
    /*auto makeCard = [](const QString& title) {
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
    grid->addWidget(makeCard("Categories"), 1, 1);*/

	QGridLayout* grid = new QGridLayout(this);
	grid->setSpacing(20);
	grid->setContentsMargins(0, 0, 0, 0);

	//==== Categorie Frame =====   
	card_categories_frame = new QFrame;

	vbox_categories = new QVBoxLayout(card_categories_frame);
	vbox_categories->setSpacing(10);
	vbox_categories->setContentsMargins(15, 15, 15, 15);

	QHBoxLayout* hbox_category_top = new QHBoxLayout;
	QLabel* lbl_categories = new QLabel("Categories");
	lbl_categories->setStyleSheet("font-size: 16px; font-weight: bold;");

	hbox_category_top->addWidget(lbl_categories);
	hbox_category_top->addStretch();

	category_list = new QListWidget;
	vbox_categories->addLayout(hbox_category_top);
	vbox_categories->addWidget(category_list);

	//==== Categorie Frame =====  
	//
	//==== Comment Frame =====   
	card_comments_frame = new QFrame;

	vbox_comments = new QVBoxLayout(card_comments_frame);
	vbox_comments->setSpacing(10);
	vbox_comments->setContentsMargins(15, 15, 15, 15);

	QHBoxLayout* hbox_comments_top = new QHBoxLayout;
	QLabel* lbl_comments = new QLabel("Comments");
	lbl_comments->setStyleSheet("font-size: 16px; font-weight: bold;");

	hbox_comments_top->addWidget(lbl_comments);
	hbox_comments_top->addStretch();

	comment_list = new QListWidget;
	vbox_comments->addLayout(hbox_comments_top);
	vbox_comments->addWidget(comment_list);

	//==== Comment Frame ===== 
	// 
	//==== Task Frame =====
	card_tasks_frame = new QFrame;

	vbox_tasks = new QVBoxLayout(card_tasks_frame);
	vbox_tasks->setSpacing(10);
	vbox_tasks->setContentsMargins(15, 15, 15, 15);
	//
	QHBoxLayout* hbox_tasks_top = new QHBoxLayout;
	QLabel* lbl_tasks = new QLabel("Tasks");
	lbl_tasks->setStyleSheet("font-size: 16px; font-weight: bold;");

	hbox_tasks_top->addWidget(lbl_tasks);
	hbox_tasks_top->addStretch();
	//
	task_list = new QListWidget;
	vbox_tasks->addLayout(hbox_tasks_top);
	vbox_tasks->addWidget(task_list);


	//==== Add frames to grid layout =====
	grid->addWidget(card_categories_frame, 0, 0);
	grid->addWidget(card_comments_frame, 0, 1);
	grid->addWidget(card_tasks_frame, 1, 0, 1, 2);

}

