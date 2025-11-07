#pragma once
#include <QWidget>

class QPushButton;
class QLineEdit;

class RegWindow : public QWidget
{
    Q_OBJECT

private:

    QString      m_username;
    QString      m_userpass;
    QLineEdit*   usern_line_edit;
    QLineEdit*   passw_line_edit;
    QPushButton* register_btn;
    QPushButton* back_auth;

public:
    RegWindow(QWidget* parent = nullptr);

    QString getName() { return m_username; };
    QString getPass() { return m_userpass; };

signals:
    void back_auth_button_reg_win_clicked();

private slots:
    void on_lineEdit_username_Edited();
    void on_lineEdit_password_Edited();
    void on_registerPushButton_reg_win_clicked();

};