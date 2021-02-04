#ifndef TABLE22DIALOG_H
#define TABLE22DIALOG_H

#include <QDialog>

namespace Ui {
class Table22Dialog;
}

class Table22Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Table22Dialog(QWidget *parent = nullptr);
    ~Table22Dialog();

private:
    Ui::Table22Dialog *ui;
};

#endif // TABLE22DIALOG_H
