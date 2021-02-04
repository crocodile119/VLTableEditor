#ifndef TABLE1MDIALOG_H
#define TABLE1MDIALOG_H

#include <QDialog>

namespace Ui {
class Table1MDialog;
}

class Table1MDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Table1MDialog(QWidget *parent = nullptr);
    ~Table1MDialog();

private:
    Ui::Table1MDialog *ui;
};

#endif // TABLE1MDIALOG_H
