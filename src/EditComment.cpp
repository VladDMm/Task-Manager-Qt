#include "headers/EditCommentW.h"
#include "headers/Task.h"
#include "headers/TaskManagerService.h"


#include <QFrame>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QCloseEvent>
#include <QListWidgetItem>

EditCommentWindow::EditCommentWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Edit Category");
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
            QTextEdit {
                background: white;
                border: 1px solid black;
                border-radius: 10px;
                font-size: 15px;
            }

        )");
    setMinimumSize(250, 200);
    edit_frame = new QFrame(this);

    QVBoxLayout* vertical_l_objects = new QVBoxLayout(edit_frame);

    confirm_btn = new QPushButton("Confirm");
    confirm_btn->setCursor(Qt::PointingHandCursor);

    cancel_btn = new QPushButton("Cancel");
    cancel_btn->setCursor(Qt::PointingHandCursor);

    text_line = new QTextEdit;
    text_line->setPlaceholderText("Text");

    vertical_l_objects->addWidget(text_line);
    vertical_l_objects->addWidget(confirm_btn);
    vertical_l_objects->addWidget(cancel_btn);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(edit_frame);

    connect(confirm_btn, &QPushButton::clicked, this, &EditCommentWindow::add_btn_pushed);
    connect(cancel_btn, &QPushButton::clicked, this, [this]() {
        this->close();
        });
}

void EditCommentWindow::add_btn_pushed()
{
    comment_text = this->text_line->toPlainText();
    Comment comment{ comment_id, comment_text.toStdString() };
    taskService_.update_comment(comment);

    QMessageBox::information(this, "Success", "Successfully.");
}

void EditCommentWindow::initialize_components()
{
    text_line->setText(comment_item->text());
    comment_id = comment_item->data(Qt::UserRole).toInt();
}

void EditCommentWindow::closeEvent(QCloseEvent* event)
{
    emit windowClosed();
    QWidget::closeEvent(event);
}

void EditCommentWindow::set_category_item(QListWidgetItem* item)
{
    comment_item = item;
}