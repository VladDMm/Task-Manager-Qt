#include "headers/EditTaskW.h"
#include "headers/Task.h"
#include "headers/TaskManagerService.h"


#include <QFrame>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QListWidgetItem>

EditTaskWindow::EditTaskWindow(QWidget* parent) : QWidget(parent)
{
	setWindowTitle("Edit Task");
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
            QLineEdit {
                background: white;
                border: 1px solid black;
                border-radius: 10px;
                font-size: 15px;
            }
            QTextEdit {
                border-radius: 10px;
                font-size: 15px;
            }
        )");

	edit_frame = new QFrame(this);

	QVBoxLayout* vertical_l_objects = new QVBoxLayout(edit_frame);

	confirm_btn = new QPushButton("Confirm");
	confirm_btn->setCursor(Qt::PointingHandCursor);

	cancel_btn = new QPushButton("Cancel");
	cancel_btn->setCursor(Qt::PointingHandCursor);

	title_line = new QLineEdit;
	title_line->setPlaceholderText("Title Task");

	description_line = new QTextEdit;
	description_line->setPlaceholderText("Description");

	//============initialize categories==================
	categorie_item = new QComboBox;

	//===================================================
	priority_lvl_item = new QComboBox;
	priority_lvl_item->addItem("Low", QVariant(0));
	priority_lvl_item->addItem("Medium", QVariant(1));
	priority_lvl_item->addItem("High", QVariant(2));
	//===================================================
	status_lvl_item = new QComboBox;
	status_lvl_item->addItem("To Do", QVariant(0));
	status_lvl_item->addItem("In Progress", QVariant(1));
	status_lvl_item->addItem("Done", QVariant(2));
	//===================================================

	vertical_l_objects->addWidget(title_line);
	vertical_l_objects->addWidget(description_line);
	vertical_l_objects->addWidget(status_lvl_item);
	vertical_l_objects->addWidget(categorie_item);
	vertical_l_objects->addWidget(priority_lvl_item);
	vertical_l_objects->addWidget(confirm_btn);
	vertical_l_objects->addWidget(cancel_btn);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(20);
	layout->setContentsMargins(20, 20, 20, 20);
	layout->addWidget(edit_frame);

	connect(confirm_btn, &QPushButton::clicked, this, &EditTaskWindow::confirm_btn_pushed);
	connect(cancel_btn, &QPushButton::clicked, this, [this]() {
		this->close();
		});

	connect(categorie_item, &QComboBox::currentIndexChanged, this, [&](uint16_t index)
		{
			category_name = categorie_item->currentText();
			temporar_category_id = categorie_item->itemData(index).toInt();
		});

	connect(priority_lvl_item, &QComboBox::currentIndexChanged, this, [&](uint16_t index)
		{
			priority_id = priority_lvl_item->itemData(index).toInt();
		});
	connect(status_lvl_item, &QComboBox::currentIndexChanged, this, [&](uint16_t index)
		{
			status_id = status_lvl_item->itemData(index).toInt();
		});
}

void EditTaskWindow::confirm_btn_pushed()
{
	QString title = this->title_line->text();
	QString desc = this->description_line->toPlainText();
	uint16_t id_task = task_item->data(Qt::UserRole).toInt();
	// if category selected
	if (!category_name.isEmpty() && category_name != "Select Category")
	{
		Task task{ static_cast<uint16_t>(task_item->data(Qt::UserRole).toInt()),
			title.toStdString(),
			desc.toStdString(), 
			static_cast<TaskStatus>(status_id),
			static_cast<TaskPriority>(priority_id)};

		taskService_.update_task(task);
		
		if(original_category_id) // ? daca a fost initial intr-o categorie atunci se face update : se face adaugare
			taskService_.update_category_for_task(id_task, Category{ temporar_category_id, category_name.toStdString() });
		taskService_.add_task_to_category(id_task, Category{ temporar_category_id, category_name.toStdString() });
		
		QMessageBox::information(this, "Success", "Successfully.");
		return;
	}
	// else
	Task task{ static_cast<uint16_t>(task_item->data(Qt::UserRole).toInt()),
		title.toStdString(),
		desc.toStdString(),
		static_cast<TaskStatus>(status_id),
		static_cast<TaskPriority>(priority_id) };

	taskService_.update_task(task);
	
	if(original_category_id) // daca a fost initial o categorie dupa care sa setat pe SELECT CATEGORY atunci se sterge legatura din DB
		taskService_.delete_task_from_category(id_task, original_category_id);

	QMessageBox::information(this, "Success", "Successfully.");
}

void EditTaskWindow::initialize_components()
{
	auto categ_map_item = taskService_.get_categories();
	
	uint16_t task_id = task_item->data(Qt::UserRole).toInt();
	Task local_task = taskService_.get_task(task_id);
	uint16_t task_category_id = local_task.get_id_category();  // category_id + task_id
	
	categorie_item->clear();
	categorie_item->addItem("Select Category", QVariant(0));

	title_line->setText(task_item->text());
	description_line->setText(local_task.get_description().data());

	// initializing category combo box
	// optimizat codul prin adaugare index direct
	for (auto& [id, category] : categ_map_item)
	{
		categorie_item->addItem(category.title.c_str(), QVariant(id));
	}

	//auto it = categ_map_item.begin();
	//while (true)
	//{
	//	it = std::find_if_not(it, categ_map_item.end(), 
	//		[&task_category_id](const std::pair<uint16_t, Category>& map_item)
	//		{ 
	//			return map_item.first == task_category_id;
	//		});
	//	if (it == categ_map_item.end())
	//		break;
	//	categorie_item->addItem(it->second.title.c_str(), QVariant(it->first));
	//	++it;
	//}
	//auto v = categ_map_item.find(task_category_id) != categ_map_item.end() ? categ_map_item.find(task_category_id)->second.title.c_str() : "Select Category";

	categorie_item->setCurrentIndex(categorie_item->findData(task_category_id));

	category_name = categorie_item->currentText();
	original_category_id = task_category_id;
	//

	// initializing priority combo box
	priority_lvl_item->setCurrentIndex(priority_lvl_item->findData(local_task.get_task_priority_to_uint()));
	//

	// initializing task status combo box
	status_lvl_item->setCurrentIndex(status_lvl_item->findData(local_task.get_task_status_to_uint()));
	//
}

void EditTaskWindow::closeEvent(QCloseEvent* event)
{
	emit windowClosed();
	QWidget::closeEvent(event);
}

void EditTaskWindow::set_task_item(QListWidgetItem* item)
{
	task_item = item;
}