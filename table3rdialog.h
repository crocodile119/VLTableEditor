#ifndef TABLE3RDIALOG_H
#define TABLE3RDIALOG_H

#include <QDialog>

namespace Ui {
class Table3RDialog;
}

class Table3RDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Table3RDialog(QWidget *parent = nullptr);
    ~Table3RDialog();

private:
    Ui::Table3RDialog *ui;
};

#endif // TABLE3RDIALOG_H
