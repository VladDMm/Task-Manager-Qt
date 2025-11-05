#include "headers/RegWindow.h"
#include "headers/User.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

Reg_Window::Reg_Window(QWidget* parent) : QWidget(parent)
{
    setStyleSheet(R"(
        QWidget {
            background-color: #ffffff;
            border-radius: 20px;
        }
        QPushButton {
            border: none;
            text-align: center;
            padding: 5px 10px;
            font-size: 15px;
            color: #444;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #f0f0f0;
        }
        QLineEdit {
            background: white;
            border: 1px solid black;
            border-radius: 10px;
            font-size: 15px;
        }
    )");
    setWindowTitle("Registration");
    setFixedSize(300, 190);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(10, 20, 10, 20);
    layout->setSpacing(10);

    register_btn = new QPushButton("Register", this);
    back_auth = new QPushButton("Back to login", this);

    usern_line_edit = new QLineEdit(this);
    passw_line_edit = new QLineEdit(this);
   
    usern_line_edit->setAlignment(Qt::AlignCenter);
    passw_line_edit->setAlignment(Qt::AlignCenter);
   
    usern_line_edit->setPlaceholderText("Username");
    passw_line_edit->setPlaceholderText("Password");

    layout->addWidget(usern_line_edit);
    layout->addWidget(passw_line_edit);
    layout->addWidget(register_btn);
    layout->addWidget(back_auth);

    connect(register_btn, &QPushButton::clicked, this, &Reg_Window::on_registerPushButton_reg_win_clicked);
    connect(back_auth, &QPushButton::clicked, this, &Reg_Window::back_auth_button_reg_win_clicked);
    connect(usern_line_edit, &QLineEdit::textEdited, this, &Reg_Window::on_lineEdit_username_Edited);
    connect(passw_line_edit, &QLineEdit::textEdited, this, &Reg_Window::on_lineEdit_password_Edited);
}

void Reg_Window::on_lineEdit_username_Edited()
{
    m_username = usern_line_edit->text();
}

void Reg_Window::on_lineEdit_password_Edited()
{
    m_userpass = usern_line_edit->text();
}

void Reg_Window::on_registerPushButton_reg_win_clicked()
{
    m_username = usern_line_edit->text();
    m_userpass = usern_line_edit->text();

    if (m_username.isEmpty() || m_userpass.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    try
    {
        current_user = User(m_username.toStdString(), m_userpass.toStdString());
        current_user.add_user();
        QMessageBox::information(this, "Success", "Successfully.");
    }
    catch (const std::runtime_error& e)
    {
        QMessageBox::warning(this, "Registration Error", e.what());
    }
   
}