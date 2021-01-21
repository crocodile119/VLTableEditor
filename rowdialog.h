#ifndef ROWDIALOG_H
#define ROWDIALOG_H

#include <QDialog>

namespace Ui {
class RowDialog;
}

class RowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RowDialog(QWidget *parent = nullptr, int* maxRow=nullptr);
    ~RowDialog();
    int* getMaxRowArray();

private slots:
    void on_empSpinBox_valueChanged(int arg1);
    void on_lea_1_1M_SpinBox_valueChanged(int arg1);
    void on_lea_3R_SpinBox_valueChanged(int arg1);

private:
    Ui::RowDialog *ui;
    int *myMaxRow;
};

#endif // ROWDIALOG_H
