#include "table23dialog.h"
#include "ui_table23dialog.h"
#include <QPixmap>

Table23Dialog::Table23Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table23Dialog)
{
    ui->setupUi(this);
    QPixmap Table_23=QPixmap(":/images/Table_23.png", "png");
    ui->Table_23->setPixmap(Table_23);
    ui->Table_23->setScaledContents(true);
}

Table23Dialog::~Table23Dialog()
{
    delete ui;
}
