#pragma once

#include <QWidget>

class QFrame;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTextEdit;

class AddCategoryWindow : public QWidget
{
    Q_OBJECT

private:
    QFrame*      edit_frame;
    QLineEdit*   title_line;
    QPushButton* cancel_btn;
    QPushButton* confirm_btn;

private slots:
    void add_btn_pushed();
    void closeEvent(QCloseEvent* event);

signals:
    void windowClosed();

public:
    AddCategoryWindow(QWidget* parent = nullptr);


};