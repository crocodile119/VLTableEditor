#include "rowdialog.h"
#include "ui_rowdialog.h"
#include <QDebug>

RowDialog::RowDialog(QWidget *parent, int *maxRow) :
    QDialog(parent),
    ui(new Ui::RowDialog)
{
    ui->setupUi(this);

    myMaxRow=new int[4];
    for(int i=0; i<4; i++){
        myMaxRow[i]=maxRow[i];

    qDebug()<< "maxRow[" << myMaxRow[i]<< "]";}

    ui->empSpinBox->setValue(myMaxRow[0]);
    ui->lea_1_1M_SpinBox->setValue(myMaxRow[1]);
    ui->lea_3R_SpinBox->setValue(myMaxRow[2]);
    ui->lea_3B_SpinBox->setValue(myMaxRow[3]);
}

RowDialog::~RowDialog()
{
    delete ui;
}

void RowDialog::on_empSpinBox_valueChanged(int arg1)
{
    myMaxRow[0]=arg1;
}

void RowDialog::on_lea_1_1M_SpinBox_valueChanged(int arg1)
{
    myMaxRow[1]=arg1;
}

void RowDialog::on_lea_3R_SpinBox_valueChanged(int arg1)
{
    myMaxRow[2]=arg1;
}

int* RowDialog::getMaxRowArray()
{
    for(int i=0; i<4; i++){
        qDebug()<< myMaxRow[i]<< "l'Array in getMaxRowArray";}

    return myMaxRow;
}
