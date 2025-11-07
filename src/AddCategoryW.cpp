#include "headers/AddCategoryW.h"

#include "headers/Task.h"
#include "headers/TaskManagerService.h"

#include <QFrame>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include <QMessageBox>

AddCategoryWindow::AddCategoryWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Add Category");
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
    title_line->setPlaceholderText("Title Category");

    vertical_l_objects->addWidget(title_line);
    vertical_l_objects->addWidget(confirm_btn);
    vertical_l_objects->addWidget(cancel_btn);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(edit_frame);

    connect(confirm_btn, &QPushButton::clicked, this, &AddCategoryWindow::add_btn_pushed);
    connect(cancel_btn, &QPushButton::clicked, this, [this]() {
        this->close();
        });
}

void AddCategoryWindow::add_btn_pushed()
{
    QString title = this->title_line->text();
    
    if (title.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter a category.");
        return;
    }
        
    taskService_.add_category(title.toStdString());
    QMessageBox::information(this, "Success", "Successfully.");
}

void AddCategoryWindow::closeEvent(QCloseEvent* event)
{
    emit windowClosed();
    QWidget::closeEvent(event);
}