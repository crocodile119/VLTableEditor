#include "table3bdialog.h"
#include "ui_table3bdialog.h"
#include <QPixmap>

Table3BDialog::Table3BDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table3BDialog)
{
    ui->setupUi(this);
    QPixmap EN_3B_Table=QPixmap(":/images/EN_Table_3B.png", "png");
    ui->EN_Table_3B->setPixmap(EN_3B_Table);
    ui->EN_Table_3B->setScaledContents(true);
}

Table3BDialog::~Table3BDialog()
{
    delete ui;
}
