#ifndef READWIDGET_H
#define READWIDGET_H

#include <QWidget>

namespace Ui {
class readWidget;
}

class readWidget : public QWidget
{
    Q_OBJECT

public:
    explicit readWidget(QWidget *parent = 0);
    ~readWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::readWidget *ui;
};

#endif // READWIDGET_H
