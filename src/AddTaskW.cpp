#include "headers/AddTaskW.h"
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

AddTaskWindow::AddTaskWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Add Task");
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
    categorie_item->addItem("Select Category", QVariant(0));
    //
    priority_lvl_item = new QComboBox;
    //===================================================
    vertical_l_objects->addWidget(title_line);
    vertical_l_objects->addWidget(description_line);
    vertical_l_objects->addWidget(categorie_item);
    vertical_l_objects->addWidget(priority_lvl_item);
    vertical_l_objects->addWidget(confirm_btn);
    vertical_l_objects->addWidget(cancel_btn);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(edit_frame);

    connect(confirm_btn, &QPushButton::clicked, this, &AddTaskWindow::add_btn_pushed);
    connect(cancel_btn, &QPushButton::clicked, this, [this]() {
        this->close();
        });

    connect(categorie_item, &QComboBox::currentIndexChanged, this, [&](uint16_t index) 
        {
            category_name = categorie_item->currentText();
            category_id = categorie_item->itemData(index).toInt(); 
        });

    connect(priority_lvl_item, &QComboBox::currentIndexChanged, this, [&](uint16_t index)
        {
            priority_name = priority_lvl_item->currentText();
            priority_id = priority_lvl_item->itemData(index).toInt();
        });
}

void AddTaskWindow::add_btn_pushed()
{
    QString title = this->title_line->text();
    QString desc = this->description_line->toPlainText();
    
    if (!category_name.isEmpty())
    {
        Task task{ 0, title.toStdString(), desc.toStdString(), TaskStatus::TO_DO, static_cast<TaskPriority>(priority_id) };
        uint16_t id_task = taskService_.add_task(std::move(task));
        taskService_.add_task_to_category(id_task, Category{ category_id, category_name.toStdString() });
        QMessageBox::information(this, "Success", "Successfully.");
        return;
    }

    Task task{ 0, title.toStdString(), desc.toStdString(), TaskStatus::TO_DO, static_cast<TaskPriority>(priority_id) };
    taskService_.add_task(std::move(task));
    QMessageBox::information(this, "Success", "Successfully.");
}

void AddTaskWindow::initialize_components()
{
    auto categ_map_item = taskService_.get_categories();
    
    if (categorie_item->count() < categ_map_item.size())
    {
        categorie_item->clear();
        categorie_item->addItem("Select Category", QVariant(0));
        for (auto& [id, cat] : categ_map_item)
        {
            categorie_item->addItem(cat.title.c_str(), QVariant(id));
        }
    }

    priority_lvl_item->addItem("Select Priority");
    priority_lvl_item->addItem("Low", QVariant(0));
    priority_lvl_item->addItem("Medium", QVariant(1));
    priority_lvl_item->addItem("High", QVariant(2));
}

void AddTaskWindow::closeEvent(QCloseEvent* event)
{
    emit windowClosed();
    QWidget::closeEvent(event);
}