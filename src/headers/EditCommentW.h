#pragma once

#include <QWidget>

class QFrame;
class QPushButton;
class QComboBox;
class QTextEdit;
class QListWidgetItem;
struct Category;

class EditCommentWindow : public QWidget
{
    Q_OBJECT

private:
    uint16_t            comment_id;
    QString             comment_text;

    QFrame*             edit_frame;
    QTextEdit*          text_line;
    QPushButton*        cancel_btn;
    QPushButton*        confirm_btn;
    QListWidgetItem*    comment_item;

private slots:
    void add_btn_pushed();
    void closeEvent(QCloseEvent* event);

public slots:
    void initialize_components();

signals:
    void windowClosed();

public:
    EditCommentWindow(QWidget* parent = nullptr);
    void set_category_item(QListWidgetItem* item);
};