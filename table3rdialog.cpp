#include "table3rdialog.h"
#include "ui_table3rdialog.h"
#include <QPixmap>

Table3RDialog::Table3RDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table3RDialog)
{
    ui->setupUi(this);
    QPixmap EN_3R_Table=QPixmap(":/images/EN_Table_3R.png", "png");
    ui->EN_Table_3R->setPixmap(EN_3R_Table);
    ui->EN_Table_3R->setScaledContents(true);
}

Table3RDialog::~Table3RDialog()
{
    delete ui;
}
