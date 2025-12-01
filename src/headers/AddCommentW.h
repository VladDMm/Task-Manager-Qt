#pragma once

#include <QWidget>

class QFrame;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTextEdit;

class AddCommentWindow : public QWidget
{
    Q_OBJECT

private:
    QFrame*      edit_frame;
    QTextEdit*   comment_line;
    QPushButton* cancel_btn;
    QPushButton* confirm_btn;

private slots:
    void add_btn_pushed();
    void closeEvent(QCloseEvent* event);

signals:
    void windowClosed();

public:
    AddCommentWindow(QWidget* parent = nullptr);


};