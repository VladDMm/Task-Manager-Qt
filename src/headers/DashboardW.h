#pragma once

#include <QWidget>

class QFrame;

class DashboardWidget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card;

public:
    DashboardWidget(QWidget* parent = nullptr);


};