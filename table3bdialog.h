#ifndef TABLE3BDIALOG_H
#define TABLE3BDIALOG_H

#include <QDialog>

namespace Ui {
class Table3BDialog;
}

class Table3BDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Table3BDialog(QWidget *parent = nullptr);
    ~Table3BDialog();

private:
    Ui::Table3BDialog *ui;
};

#endif // TABLE3BDIALOG_H
