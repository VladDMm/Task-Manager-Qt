#include "headers/AddCommentW.h"

#include "headers/Task.h"
#include "headers/TaskManagerService.h"

#include <QFrame>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QCloseEvent>
#include <QMessageBox>

AddCommentWindow::AddCommentWindow(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Add Comment");
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

    comment_line = new QTextEdit;
    comment_line->setPlaceholderText("Text");

    vertical_l_objects->addWidget(comment_line);
    vertical_l_objects->addWidget(confirm_btn);
    vertical_l_objects->addWidget(cancel_btn);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(edit_frame);

    connect(confirm_btn, &QPushButton::clicked, this, &AddCommentWindow::add_btn_pushed);
    connect(cancel_btn, &QPushButton::clicked, this, [this]() {
        this->close();
        });
}

void AddCommentWindow::add_btn_pushed()
{
    QString txt = this->comment_line->toPlainText();

    if (txt.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter a comment.");
        return;
    }

    try
    {
        taskService_.add_comment(txt.toStdString());
        QMessageBox::information(this, "Success", "Successfully.");
    }
    catch (const std::exception& e)
    {
        QMessageBox::warning(this, "Error", e.what());
        return;
    }
}

void AddCommentWindow::closeEvent(QCloseEvent* event)
{
    emit windowClosed();
    QWidget::closeEvent(event);
}