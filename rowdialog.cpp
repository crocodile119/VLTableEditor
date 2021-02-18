#include "rowdialog.h"
#include "ui_rowdialog.h"
#include <QDebug>

const int RowDialog::TABLES=4;

RowDialog::RowDialog(QWidget *parent, std::array<int, TABLES> maxRow) :
    QDialog(parent),
    ui(new Ui::RowDialog),myMaxRow{}
{
    ui->setupUi(this);
    std::copy(maxRow.begin(), maxRow.end(), myMaxRow.begin());

    ui->empSpinBox->setValue(myMaxRow.at(0));
    ui->lea_1_1M_SpinBox->setValue(myMaxRow.at(1));
    ui->lea_3R_SpinBox->setValue(myMaxRow.at(2));
    ui->lea_3B_SpinBox->setValue(myMaxRow.at(3));
}

RowDialog::~RowDialog()
{
    delete ui;
}

void RowDialog::on_empSpinBox_valueChanged(int arg1)
{
    myMaxRow.at(0)=arg1;
}

void RowDialog::on_lea_1_1M_SpinBox_valueChanged(int arg1)
{
    myMaxRow.at(1)=arg1;
}

void RowDialog::on_lea_3R_SpinBox_valueChanged(int arg1)
{
    myMaxRow.at(2)=arg1;
}

void RowDialog::on_lea_3B_SpinBox_valueChanged(int arg1)
{
    myMaxRow.at(3)=arg1;
}

std::array<int, RowDialog::TABLES> RowDialog::getMaxRowArray()
{
    return myMaxRow;
}
