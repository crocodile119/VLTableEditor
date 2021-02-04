#include "table1mdialog.h"
#include "ui_table1mdialog.h"
#include <QPixmap>

Table1MDialog::Table1MDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table1MDialog)
{
    ui->setupUi(this);
    QPixmap EN_1M_Table=QPixmap(":/images/EN_Table_1M.png", "png");
    ui->EN_Table_1M->setPixmap(EN_1M_Table);
    ui->EN_Table_1M->setScaledContents(true);
}

Table1MDialog::~Table1MDialog()
{
    delete ui;
}
