#include "headers/Auth_Window.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

Auth_Window::Auth_Window(QWidget* parent) : QWidget(parent)
{
    setStyleSheet(R"(
        QWidget {
            background-color: #ffffff;
            border-radius: 20px;
        }
        QPushButton {
            border: none;
            text-align: center;
            padding: 7px 10px;
            font-size: 16px;
            color: #444;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
            border: none;
        }
        QLineEdit {
            background: white;
            border: 1px solid black;
            border-radius: 10px;
            font-size: 15px;
        }
    )");
    setWindowTitle("Authorization");
    setFixedSize(300, 190);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 20, 10, 20);
    layout->setSpacing(10);
    
    login_btn = new QPushButton("Login", this);
    register_btn = new QPushButton("Register now", this);
    
    usern_line_edit = new QLineEdit(this);
    passw_line_edit = new QLineEdit(this);
    
    usern_line_edit->setAlignment(Qt::AlignCenter);
    passw_line_edit->setAlignment(Qt::AlignCenter);

    usern_line_edit->setPlaceholderText("Username");
    passw_line_edit->setPlaceholderText("Password");

    layout->addWidget(usern_line_edit);
    layout->addWidget(passw_line_edit);
    layout->addWidget(login_btn);
    layout->addWidget(register_btn);


    connect(login_btn, &QPushButton::clicked, this, &Auth_Window::login_button_clicked);
    connect(register_btn, &QPushButton::clicked, this, &Auth_Window::register_button_ath_win_clicked);
    connect(usern_line_edit, &QLineEdit::textEdited, this, &Auth_Window::on_lineEdit_username_Edited);
    connect(passw_line_edit, &QLineEdit::textEdited, this, &Auth_Window::on_lineEdit_password_Edited);
}

void Auth_Window::on_lineEdit_username_Edited()
{
    m_username = usern_line_edit->text();
}

void Auth_Window::on_lineEdit_password_Edited()
{
    m_userpass = passw_line_edit->text();
}