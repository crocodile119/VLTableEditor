#include "readwidget.h"
#include "ui_readwidget.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFile>


readWidget::readWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readWidget)
{
    ui->setupUi(this);
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

readWidget::~readWidget()
{
    delete ui;
}

void readWidget::on_pushButton_clicked()
{
    QFile file("text.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Laser Project"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);


    QApplication::setOverrideCursor(Qt::WaitCursor);

        for (int column = 0; column < 5; ++column)
        {
            for  (int row = 0; row < 5; ++row)  {

               QString str;
                in >> str;

                QTableWidgetItem* item = new QTableWidgetItem(QString(str));
                ui->tableWidget->setItem(row,column,item);
                }
            }

    QApplication::restoreOverrideCursor();
}
