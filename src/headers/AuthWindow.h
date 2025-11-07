#pragma once

#include <QWidget>

class QPushButton;
class QLineEdit;

class AuthWindow : public QWidget
{
	Q_OBJECT

private:
    QString      m_username;
    QString      m_userpass;
    QLineEdit*   usern_line_edit;
    QLineEdit*   passw_line_edit;
    QPushButton* login_btn;
    QPushButton* register_btn;

public:
    AuthWindow(QWidget* parent = nullptr);

    QString getLogin() { return m_username; };
    QString getPass() { return m_userpass; };

signals:
    void login_button_clicked();
    void register_button_ath_win_clicked();

private slots:
    void on_lineEdit_username_Edited();
    void on_lineEdit_password_Edited();

};