#include "headers/MyTaskW.h"
#include "headers/AddTaskW.h"
#include "headers/AddCategoryW.h"
#include "headers/TaskManagerService.h"
#include "mysql/jdbc.h"


#include <QFrame>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
#include <QListWidget>
#include <QGraphicsDropShadowEffect>

MyTasksWidget::MyTasksWidget(QWidget* parent) : QWidget(parent)
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

	//==== Categorie Frame =====   
	card_categories_frame = new QFrame;

	vbox_categories = new QVBoxLayout(card_categories_frame);
	vbox_categories->setSpacing(10);
	vbox_categories->setContentsMargins(15, 15, 15, 15);

	QHBoxLayout* hbox_category_top = new QHBoxLayout;
	new_categorie_btn = new QPushButton("+ New Category");
	new_categorie_btn->setCursor(Qt::PointingHandCursor);
	QLabel* lbl_categories = new QLabel("Categories");
	lbl_categories->setStyleSheet("font-size: 16px; font-weight: bold;");

	hbox_category_top->addWidget(lbl_categories);
	hbox_category_top->addStretch();
	hbox_category_top->addWidget(new_categorie_btn);

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
	new_comment_btn = new QPushButton("+ New Comment");
	new_comment_btn->setCursor(Qt::PointingHandCursor);
	QLabel* lbl_comments = new QLabel("Comments");
	lbl_comments->setStyleSheet("font-size: 16px; font-weight: bold;");

	hbox_comments_top->addWidget(lbl_comments);
	hbox_comments_top->addStretch();
	hbox_comments_top->addWidget(new_comment_btn);

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
	new_task_btn = new QPushButton("+ New Task");
	new_task_btn->setCursor(Qt::PointingHandCursor);
	QLabel* lbl_tasks = new QLabel("Tasks");
	lbl_tasks->setStyleSheet("font-size: 16px; font-weight: bold;");

	hbox_tasks_top->addWidget(lbl_tasks);
	hbox_tasks_top->addStretch();
	hbox_tasks_top->addWidget(new_task_btn);
	//
	task_list = new QListWidget;
	vbox_tasks->addLayout(hbox_tasks_top);
	vbox_tasks->addWidget(task_list);

	task_list->setContextMenuPolicy(Qt::CustomContextMenu);
	//====== Task Frame =====

	//==== Add frames to grid layout =====
	grid->addWidget(card_categories_frame, 0, 0);
	grid->addWidget(card_comments_frame, 0, 1);
	grid->addWidget(card_tasks_frame, 1, 0, 1, 2);

	task_window = new AddTaskWindow;
	category_window = new AddCategoryWindow;

	connect(task_list, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
	connect(new_task_btn, &QPushButton::clicked, this, &MyTasksWidget::show_add_task_window);
	connect(new_categorie_btn, &QPushButton::clicked, this, &MyTasksWidget::show_add_category_window);
	connect(task_window, &AddTaskWindow::windowClosed, this, &MyTasksWidget::refresh_task_list);
	connect(category_window, &AddCategoryWindow::windowClosed, this, &MyTasksWidget::refresh_category_list);
	connect(new_task_btn, &QPushButton::clicked, task_window, &AddTaskWindow::initialize_components);
}

void MyTasksWidget::show_add_task_window()
{
	task_window->show();
}

void MyTasksWidget::show_add_category_window()
{
	category_window->show();
}

void MyTasksWidget::refresh_task_list()
{
	auto tasks = taskService_.get_tasks();
	if (task_list->count() < tasks.size())
	{
		task_list->clear();
		for (auto& [id, task] : tasks)
		{
			QListWidgetItem* task_item = new QListWidgetItem;
			task_item->setText(task.get_title().data());
			task_item->setData(Qt::UserRole, id);
			task_list->addItem(task_item);
		}
		card_tasks_frame->update();
	}
}

void MyTasksWidget::refresh_category_list()
{
	auto categories = taskService_.get_categories();
	if (category_list->count() < categories.size())
	{
		category_list->clear();
		for (auto& [id, category] : categories)
		{
			QListWidgetItem* categ_item = new QListWidgetItem;
			categ_item->setText(category.title.c_str());
			categ_item->setData(Qt::UserRole, id);
			category_list->addItem(categ_item);
		}
		card_categories_frame->update();
	}
}

void MyTasksWidget::showContextMenu(const QPoint& pos) {
	// Get the item at the position
	QListWidgetItem* item = task_list->itemAt(pos);
	if (!item) {
		return; // No item at this position
	}

	// Create the context menu
	QMenu* contextMenu = new QMenu(this);
	contextMenu->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
	contextMenu->setAttribute(Qt::WA_TranslucentBackground);
	
	contextMenu->setStyleSheet(R"(
    QMenu {
        background-color: #faf8f2;
        border-radius: 15px;
        border: none;
        padding: 8px;
        margin: 0px;
    }

    QMenu::item {
        border-radius: 10px;
        padding: 8px 20px;
        color: #333;
        background-color: transparent;
        margin: 3px 0;
    }

    QMenu::item:selected {
        background-color: #357AE8;
        color: white;
    }

    QMenu::item:pressed {
        background-color: #2d65c5;
    }
)");

	// Add actions to the menu
	QAction* deleteAction = contextMenu->addAction("Delete Item");
	QAction* editAction = contextMenu->addAction("Edit Item");

	connect(deleteAction, &QAction::triggered, [this, item]() 
		{
			taskService_.delete_task(item->data(Qt::UserRole).toInt());
			delete task_list->takeItem(task_list->row(item));
		});

	// Map the local position to global screen coordinates
	QPoint globalPos = task_list->viewport()->mapToGlobal(pos);

	contextMenu->popup(task_list->viewport()->mapToGlobal(pos));
}
