#include "table22dialog.h"
#include "ui_table22dialog.h"
#include <QPixmap>

Table22Dialog::Table22Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table22Dialog)
{
    ui->setupUi(this);
    QPixmap Table_22=QPixmap(":/images/Table_22.png", "png");
    ui->Table_22->setPixmap(Table_22);
    ui->Table_22->setScaledContents(true);
}

Table22Dialog::~Table22Dialog()
{
    delete ui;
}
