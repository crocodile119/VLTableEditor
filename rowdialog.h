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
    const static int TABLES;
    explicit RowDialog(QWidget *parent, std::array<int, 4>);
    ~RowDialog();
    std::array<int, 4> getMaxRowArray();

private slots:
    void on_empSpinBox_valueChanged(int arg1);
    void on_lea_1_1M_SpinBox_valueChanged(int arg1);
    void on_lea_3R_SpinBox_valueChanged(int arg1);
    void on_lea_3B_SpinBox_valueChanged(int arg1);

private:
    Ui::RowDialog *ui;
    std::array<int, 4> myMaxRow;
};

#endif // ROWDIALOG_H
