#ifndef TABLE23DIALOG_H
#define TABLE23DIALOG_H

#include <QDialog>

namespace Ui {
class Table23Dialog;
}

class Table23Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Table23Dialog(QWidget *parent = nullptr);
    ~Table23Dialog();

private:
    Ui::Table23Dialog *ui;
};

#endif // TABLE23DIALOG_H
