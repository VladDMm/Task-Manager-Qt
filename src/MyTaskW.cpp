#include "headers/MyTaskW.h"
#include "headers/AddTaskW.h"
#include "headers/AddCategoryW.h"
#include "headers/TaskManagerService.h"
#include "headers/EditTaskW.h"
#include "headers/EditCategoryW.h"
#include "headers/EditCommentW.h"
#include "headers/AddCommentW.h"
#include "mysql/jdbc.h"

#include <QFrame>
#include <QSet>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPoint>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGraphicsDropShadowEffect>

static uint16_t flag_edit_item = 0;

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
			QMessageBox {
				background-color: #ffffff;
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
	category_list->setContextMenuPolicy(Qt::CustomContextMenu);
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
	comment_list->setContextMenuPolicy(Qt::CustomContextMenu);
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

	task_window =			new AddTaskWindow;
	edit_task_window =		new EditTaskWindow;
	category_window =		new AddCategoryWindow;
	edit_category_window =	new EditCategoryWindow;
	comment_window =		new AddCommentWindow;
	edit_comment_window =	new EditCommentWindow;

	connect(task_list, &QListView::customContextMenuRequested, this, [this](const QPoint& p) 
		{ 
			flag_edit_item = 1; this->showContextMenu(p); 
		});
	connect(task_list, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) 
		{ 
			this->show_edit_task_window(item);
		});
	connect(category_list, &QListView::customContextMenuRequested, this, [this](const QPoint& p) 
		{ 
			if (edit_task_window->isEnabled())
				edit_task_window->close();
			flag_edit_item = 2; this->showContextMenu(p); 
		});
	connect(category_list, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) 
		{
			if (edit_task_window->isEnabled())
				edit_task_window->close();
			this->show_edit_category_window(item);
		});
	connect(comment_list, &QListView::customContextMenuRequested, this, [this](const QPoint& p) 
		{ 
			flag_edit_item = 3; this->showContextMenu(p); 
		});
	connect(comment_list, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem* item) 
		{
			if (edit_task_window->isEnabled())
				edit_task_window->close();
			this->show_edit_comment_window(item);
		});

	connect(new_task_btn, &QPushButton::clicked, this, &MyTasksWidget::show_add_task_window);
	connect(new_task_btn, &QPushButton::clicked, task_window, &AddTaskWindow::initialize_components);
	connect(new_categorie_btn, &QPushButton::clicked, this, &MyTasksWidget::show_add_category_window);
	connect(new_comment_btn, &QPushButton::clicked, this, &MyTasksWidget::show_add_comment_window);
	connect(comment_window, &AddCommentWindow::windowClosed, this, &MyTasksWidget::refresh_comment_list);
	connect(edit_comment_window, &EditCommentWindow::windowClosed, this, &MyTasksWidget::refresh_comment_list);
	connect(task_window, &AddTaskWindow::windowClosed, this, &MyTasksWidget::refresh_task_list);
	connect(edit_task_window, &EditTaskWindow::windowClosed, this, &MyTasksWidget::refresh_task_list);
	connect(category_window, &AddCategoryWindow::windowClosed, this, &MyTasksWidget::refresh_category_list);
	connect(edit_category_window, &EditCategoryWindow::windowClosed, this, &MyTasksWidget::refresh_category_list);

}

void MyTasksWidget::show_add_task_window()
{
	task_window->show();
}
void MyTasksWidget::show_add_comment_window()
{
	comment_window->show();
}
void MyTasksWidget::show_edit_task_window(QListWidgetItem* item)
{
	edit_task_window->set_task_item(item);
	edit_task_window->initialize_components();
	edit_task_window->show();
}

void MyTasksWidget::show_edit_category_window(QListWidgetItem* item)
{
	edit_category_window->set_category_item(item);
	edit_category_window->initialize_components();
	edit_category_window->show();
}

void MyTasksWidget::show_edit_comment_window(QListWidgetItem* item)
{
	edit_comment_window->set_category_item(item);
	edit_comment_window->initialize_components();
	edit_comment_window->show();
}

void MyTasksWidget::show_add_category_window()
{
	category_window->show();
}

void MyTasksWidget::refresh_task_list()
{
	auto tasks = taskService_.get_tasks();
	QSet<uint16_t> current_ids;

	for (uint16_t i = 0; i < task_list->count(); ++i)
	{
		// salvez id-urile pentru comparare ulterioare daca exista in lista sau nu
		current_ids.insert(task_list->item(i)->data(Qt::UserRole).toInt());
	}

	for (auto& [id, task] : tasks)
	{
		if (!current_ids.contains(id)) // daca nu exista task-ul in lista, il adaug
		{
			QListWidgetItem* task_item = new QListWidgetItem;
			task_item->setText(task.get_title().data());
			task_item->setData(Qt::UserRole, id);
			task_list->addItem(task_item);
		}
		else // daca exista task-ul in lista, doar actualizez titlul
		{
			for (uint16_t i = 0; i < task_list->count(); ++i)
			{
				if (task_list->item(i)->data(Qt::UserRole).toInt() == id)
				{
					task_list->item(i)->setText(task.get_title().data());
					break;
				}
			}
		}
	}

	/*if (flag)
	{
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
	else
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
	}*/

	card_tasks_frame->update();
}

void MyTasksWidget::refresh_category_list()
{
	auto categories = taskService_.get_categories();

	QSet<uint16_t> current_ids;

	for (uint16_t i = 0; i < category_list->count(); ++i)
	{
		// salvez id-urile pentru comparare ulterioare daca exista in lista sau nu
		current_ids.insert(category_list->item(i)->data(Qt::UserRole).toInt());
	}

	for (auto& [id, category] : categories)
	{
		if (!current_ids.contains(id)) // daca nu exista categoria in lista, o adaug
		{
			QListWidgetItem* category_item = new QListWidgetItem;
			category_item->setText(category.title.c_str());
			category_item->setData(Qt::UserRole, id);
			category_list->addItem(category_item);
		}
		else // daca exista categoria in lista, doar actualizez titlul
		{
			for (uint16_t i = 0; i < category_list->count(); ++i)
			{
				if (category_list->item(i)->data(Qt::UserRole).toInt() == id)
				{
					category_list->item(i)->setText(category.title.c_str());
					break;
				}
			}
		}
	}
	card_categories_frame->update();

	//if (flag)
	//	if (category_list->count() < categories.size())
	//	{
	//		category_list->clear();
	//		for (auto& [id, category] : categories)
	//		{
	//			QListWidgetItem* categ_item = new QListWidgetItem;
	//			categ_item->setText(category.title.c_str());
	//			categ_item->setData(Qt::UserRole, id);
	//			category_list->addItem(categ_item);
	//		}
	//		card_categories_frame->update();
	//	}
	//	else
	//	{
	//		category_list->clear();
	//		for (auto& [id, category] : categories)
	//		{
	//			QListWidgetItem* categ_item = new QListWidgetItem;
	//			categ_item->setText(category.title.c_str());
	//			categ_item->setData(Qt::UserRole, id);
	//			category_list->addItem(categ_item);
	//		}
	//		card_categories_frame->update();
	//	}
}

void MyTasksWidget::refresh_comment_list()
{
	auto comments = taskService_.get_comments();

	QSet<uint16_t> current_ids;

	for (uint16_t i = 0; i < comment_list->count(); ++i)
	{
		// salvez id-urile pentru comparare ulterioare daca exista in lista sau nu
		current_ids.insert(comment_list->item(i)->data(Qt::UserRole).toInt());
	}

	for (auto& [id, comment] : comments)
	{
		if (!current_ids.contains(id)) // daca nu exista comentariul in lista, o adaug
		{
			QListWidgetItem* comment_item = new QListWidgetItem;
			comment_item->setText(comment.description.c_str());
			comment_item->setData(Qt::UserRole, id);
			comment_list->addItem(comment_item);
		}
		else // daca exista comentariul in lista, doar actualizez descrierea
		{
			for (uint16_t i = 0; i < comment_list->count(); ++i)
			{
				if (comment_list->item(i)->data(Qt::UserRole).toInt() == id)
				{
					comment_list->item(i)->setText(comment.description.c_str());
					break;
				}
			}
		}
	}
	card_comments_frame->update();

	//if (flag)
	//	if (category_list->count() < categories.size())
	//	{
	//		category_list->clear();
	//		for (auto& [id, category] : categories)
	//		{
	//			QListWidgetItem* categ_item = new QListWidgetItem;
	//			categ_item->setText(category.title.c_str());
	//			categ_item->setData(Qt::UserRole, id);
	//			category_list->addItem(categ_item);
	//		}
	//		card_categories_frame->update();
	//	}
	//	else
	//	{
	//		category_list->clear();
	//		for (auto& [id, category] : categories)
	//		{
	//			QListWidgetItem* categ_item = new QListWidgetItem;
	//			categ_item->setText(category.title.c_str());
	//			categ_item->setData(Qt::UserRole, id);
	//			category_list->addItem(categ_item);
	//		}
	//		card_categories_frame->update();
	//	}
}

void MyTasksWidget::showContextMenu(const QPoint& pos) {
	// Get the item at the position
	QListWidgetItem* item;
	switch (flag_edit_item)
	{
	case 1: // edit task widget
		item = task_list->itemAt(pos);
		break;

	case 2: // edit category widget
		item = category_list->itemAt(pos);
		break;

	case 3: // edit comment widget
		item = comment_list->itemAt(pos);
		break;

	default: item = nullptr;
		break;
	}

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
			switch (flag_edit_item)
			{
			case 1:
				taskService_.delete_task(item->data(Qt::UserRole).toInt());
				delete task_list->takeItem(task_list->row(item));
				break;

			case 2:
				taskService_.delete_category(item->data(Qt::UserRole).toInt());
				delete category_list->takeItem(category_list->row(item));
				break;

			case 3:
				try
				{
					taskService_.delete_comment(item->data(Qt::UserRole).toInt());
					delete comment_list->takeItem(comment_list->row(item));
				}
				catch (const std::exception& e)
				{
					QMessageBox::warning(this, "Error", e.what());
					return;
				}
				
				break;

			default:
				break;
			}
		});

	connect(editAction, &QAction::triggered, [this, item]()
		{
			switch (flag_edit_item)
			{
			case 1: 
				show_edit_task_window(item);
				break;

			case 2: 
				show_edit_category_window(item);
				break;

			case 3:
				show_edit_comment_window(item);
				break;

			default:
				break;
			}		
		});

	// Map the local position to global screen coordinates
	QPoint globalPos;
	switch (flag_edit_item)
	{
	case 1: 
		globalPos = task_list->viewport()->mapToGlobal(pos);
		contextMenu->popup(task_list->viewport()->mapToGlobal(pos));
		break;

	case 2:
		globalPos = category_list->viewport()->mapToGlobal(pos);
		contextMenu->popup(category_list->viewport()->mapToGlobal(pos));
		break;

	case 3:
		globalPos = comment_list->viewport()->mapToGlobal(pos);
		contextMenu->popup(comment_list->viewport()->mapToGlobal(pos));
		break;

	default:
		break;
	}	
}
