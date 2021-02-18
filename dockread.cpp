#include "dockread.h"
#include "ui_dockread.h"

DockRead::DockRead(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DockRead)
{
    ui->setupUi(this);
}

DockRead::~DockRead()
{
    delete ui;
}

void DockRead::clearAsciiDataTable()
{
    ui->asciiDataTable->clearContents();
}

QTableWidgetItem* DockRead::getTableItem(int row, int column)
{
    QTableWidgetItem* ptr= ui->asciiDataTable->item(row,column);
    return ptr;
}

void DockRead::setTableItem(int row, int column, QTableWidgetItem* item)
{
    ui->asciiDataTable->setItem(row, column, item);
}

void DockRead::setTableRowCount(int row)
{
    ui->asciiDataTable->setRowCount(row);
}

void DockRead::setTableColumnCount(int column)
{
    ui->asciiDataTable->setColumnCount(column);
}

void DockRead::setTableHorizontalHeaderLabels(const QStringList &labels)
{
    ui->asciiDataTable->setHorizontalHeaderLabels(labels);
}

void DockRead::setLabel(const QString &label)
{
    ui->label->setText(label);
}

QString DockRead::getLabel()
{
    return ui->label->text();
}
