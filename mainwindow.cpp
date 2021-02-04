#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include "empdata.h"
#include "leadata.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "dockread.h"
#include "ui_dockread.h"
#include "rowdialog.h"
#include "ui_rowdialog.h"
#include "table1mdialog.h"
#include "ui_table1mdialog.h"
#include "table3rdialog.h"
#include "ui_table3rdialog.h"
#include "table3bdialog.h"
#include "ui_table3bdialog.h"
#include "table22dialog.h"
#include "ui_table22dialog.h"
#include "table23dialog.h"
#include "ui_table23dialog.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

using std::ifstream;

#include <iomanip>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    myDockRead= new DockRead();
    addDockWidget(Qt::TopDockWidgetArea, this->myDockRead);

    ui->setupUi(this);

    tableGroup = new QActionGroup(this);

    tableGroup->addAction(ui->actionEMP);
    tableGroup->addAction(ui->actionLEA_Classi_1_e_1M);
    tableGroup->addAction(ui->actionLEA_Classe_3R);
    tableGroup->addAction(ui->actionLEA_Classe_3B);

    QIcon iconWin;
    iconWin.addFile(QStringLiteral(":/images/ico.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(iconWin);

    myBinaryData=EMP;
    EMP_Table=true;
    setDataHeader();

    setInformation();

    QPixmap EN_1M_Table=QPixmap(":/images/EN_Table_1M.png", "png");
    QPixmap EN_3R_Table=QPixmap(":/images/EN_Table_3R.png", "png");
    QPixmap EN_3B_Table=QPixmap(":/images/EN_Table_3B.png", "png");

    readAsciiFile();
    writeAsciiTable();
    writeBinaryFile();
    readBinaryFile();
    writeBinarytable();
}

void MainWindow::readAsciiTable()
{
for(int row=0; row<maxRow[int(myBinaryData)]; row++) {
    int column=0;

    if(myBinaryData==EMP)
{
    myEmpData[row].formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
    column++;
    myEmpData[row].wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData[row].wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData[row].time1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData[row].time2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData[row].CA=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData[row].CB=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData[row].CC=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData[row].CE=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData[row].t=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData[row].effects=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData[row].formula=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData[row].sort=myDockRead->getTableItem(row,column)->text().toInt();
    }
    else
    {
     myLeaData[row].formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
     column++;
     myLeaData[row].wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData[row].wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData[row].time1=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData[row].time2=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData[row].C1=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].C2=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].C3=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].C4=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].C5=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].C6=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].C7=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].t=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].effects=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData[row].formula=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData[row].sort=myDockRead->getTableItem(row,column)->text().toInt();
    }
    }
}
void MainWindow::readBinaryTable()
{
for(int row=0; row<maxRow[int(myBinaryData)]; row++) {
  int column=0;
    if(myBinaryData==EMP)
{
    myCodedEmpData[row].formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
    column++;
    myCodedEmpData[row].wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData[row].wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData[row].time1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData[row].time2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData[row].CA=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData[row].CB=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData[row].CC=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData[row].CE=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData[row].t=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData[row].effects=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData[row].formula=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData[row].sort=myDockRead->getTableItem(row,column)->text().toInt();
    }
    else
    {
     myCodedLeaData[row].formulaNumber=ui->binaryTable->item(row, column)->text().toInt();
     column++;
     myCodedLeaData[row].wavelenght1=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData[row].wavelenght2=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData[row].time1=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData[row].time2=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData[row].C1=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].C2=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].C3=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].C4=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].C5=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].C6=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].C7=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].t=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].effects=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData[row].formula=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData[row].sort=ui->binaryTable->item(row,column)->text().toInt();
    }
}
}

void MainWindow::writeAsciiFile()
{
// ofstream constructor opens file
    std::ofstream outVL_DataFile(filename, std::ios::out | std::ofstream::trunc);
// exit program if unable to create file
     if ( !outVL_DataFile ) // overloaded ! operator
     {
        qDebug() << "Il file non può essere aperto";
        exit( 1 );
    } // end if

     QApplication::setOverrideCursor(Qt::WaitCursor);

     for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
       {

       if(EMP_Table){
          outVL_DataFile << myEmpData[row].formulaNumber << " " << myEmpData[row].wavelenght1 << " " << myEmpData[row].wavelenght2 << " " <<
                       myEmpData[row].time1 << " " << myEmpData[row].time2 << " " << myEmpData[row].CA << " " << myEmpData[row].CB << " " <<
                       myEmpData[row].CC << " " << myEmpData[row].CE << " " << myEmpData[row].t << " " <<  myEmpData[row].effects << " " <<
                       myEmpData[row].formula << " " << myEmpData[row].sort <<" \n";}
                 else{
          outVL_DataFile << myLeaData[row].formulaNumber << " " << myLeaData[row].wavelenght1 << " " << myLeaData[row].wavelenght2 << " " <<
                       myLeaData[row].time1 << " " << myLeaData[row].time2 << " " << myLeaData[row].C1 << " " << myLeaData[row].C2 << " " <<
                       myLeaData[row].C3 << " " << myLeaData[row].C4 << " " << myLeaData[row].C5 << " " << myLeaData[row].C6 << " " <<
                       myLeaData[row].C7 << " " << myLeaData[row].t << " " << myLeaData[row].effects << " " <<
                       myLeaData[row].formula << " " << myLeaData[row].sort <<" \n";}
     }
}
/****************************************************************************************
 * Legge i dati non codificati nela struttura myLimitData[] e codifica in file binario  *
 ****************************************************************************************/

void MainWindow::writeBinaryFile()
{

 QFile file(QString::fromStdString(binaryfilename));
 if (!file.open(QIODevice::WriteOnly)) {
     QMessageBox::warning(this, tr("VL Table Editor"),
                          tr("Cannot write file %1:\n%2.")
                          .arg(file.fileName())
                          .arg(file.errorString()));
 }

 QDataStream out(&file);
 out.setVersion(QDataStream::Qt_4_3);

 QApplication::setOverrideCursor(Qt::WaitCursor);

for(int row=0; row<maxRow[int(myBinaryData)]; row++) {
    if(EMP_Table){
        out << myEmpData[row].formulaNumber << myEmpData[row].wavelenght1 << myEmpData[row].wavelenght2
            << myEmpData[row].time1 << myEmpData[row].time2 << myEmpData[row].CA << myEmpData[row].CB
            << myEmpData[row].CC << myEmpData[row].CE << myEmpData[row].t << myEmpData[row].effects
            << myEmpData[row].formula << myEmpData[row].sort;
            }
    else
    {    
        out << myLeaData[row].formulaNumber << myLeaData[row].wavelenght1 << myLeaData[row].wavelenght2
            << myLeaData[row].time1 << myLeaData[row].time2 << myLeaData[row].C1 << myLeaData[row].C2
            << myLeaData[row].C3 << myLeaData[row].C4 << myLeaData[row].C5 << myLeaData[row].C6
            << myLeaData[row].C7 << myLeaData[row].t << myLeaData[row].effects << myLeaData[row].formula
            << myLeaData[row].sort;
           }
   }
          QApplication::restoreOverrideCursor();
}

/*****************************************************
 * Legge il file di testo  e scrive la tabella ascii *
 *****************************************************/

void MainWindow::readAsciiFile()
{

// ifstream constructor opens the file
std::ifstream inVL_DataFile(filename, std::ios::in );

if ( !inVL_DataFile ) {
    qDebug() << "Il file non può essere aperto\n";
       exit( 1 );
}

for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
  {

  if(EMP_Table){
     inVL_DataFile >> myEmpData[row].formulaNumber >> myEmpData[row].wavelenght1 >> myEmpData[row].wavelenght2 >>
                  myEmpData[row].time1 >> myEmpData[row].time2 >> myEmpData[row].CA >> myEmpData[row].CB >>
                  myEmpData[row].CC >> myEmpData[row].CE >> myEmpData[row].t >> myEmpData[row].effects >>
                  myEmpData[row].formula >> myEmpData[row].sort;}
            else{
     inVL_DataFile >> myLeaData[row].formulaNumber >> myLeaData[row].wavelenght1 >> myLeaData[row].wavelenght2 >>
                  myLeaData[row].time1 >> myLeaData[row].time2 >> myLeaData[row].C1 >> myLeaData[row].C2 >>
                  myLeaData[row].C3 >> myLeaData[row].C4 >> myLeaData[row].C5 >> myLeaData[row].C6 >>
                  myLeaData[row].C7 >> myLeaData[row].t >> myLeaData[row].effects >>
                  myLeaData[row].formula >> myLeaData[row].sort;}
    }
}

void MainWindow::readBinaryFile()
{
QFile file(QString::fromStdString(binaryfilename));
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("VL Table Editor"),
        tr("Cannot read file %1:\n%2.")
            .arg(file.fileName())
            .arg(file.errorString()));
       }

       QDataStream in(&file);
       in.setVersion(QDataStream::Qt_4_3);

        for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
         {
         if(EMP_Table){
                in >> myCodedEmpData[row].formulaNumber >> myCodedEmpData[row].wavelenght1 >> myCodedEmpData[row].wavelenght2 >>
                      myCodedEmpData[row].time1 >> myCodedEmpData[row].time2 >> myCodedEmpData[row].CA >> myCodedEmpData[row].CB >>
                      myCodedEmpData[row].CC >> myCodedEmpData[row].CE >> myCodedEmpData[row].t >> myCodedEmpData[row].effects >>
                      myCodedEmpData[row].formula >> myCodedEmpData[row].sort;
                      }
         else {
                in >> myCodedLeaData[row].formulaNumber >> myCodedLeaData[row].wavelenght1 >> myCodedLeaData[row].wavelenght2 >>
                      myCodedLeaData[row].time1 >> myCodedLeaData[row].time2 >> myCodedLeaData[row].C1 >> myCodedLeaData[row].C2 >>
                      myCodedLeaData[row].C3 >> myCodedLeaData[row].C4 >> myCodedLeaData[row].C5 >> myCodedLeaData[row].C6 >>
                      myCodedLeaData[row].C7 >> myCodedLeaData[row].t >> myCodedLeaData[row].effects >> myCodedLeaData[row].formula >>
                      myCodedLeaData[row].sort;
                      }
            }
}

void MainWindow::writeAsciiTable()
{
    for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
    {
    int column=0;
    if(myBinaryData==EMP)
    {
         QString formulaNumberString=QString::number(myEmpData[row].formulaNumber);
         QTableWidgetItem* item = new QTableWidgetItem(QString(formulaNumberString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Wavelenght1String=QString::number(myEmpData[row].wavelenght1);
         item = new QTableWidgetItem(QString(Wavelenght1String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Wavelenght2String = QString::number(myEmpData[row].wavelenght2);
         item = new QTableWidgetItem(QString(Wavelenght2String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Time1String = QString::number(myEmpData[row].time1);
         item = new QTableWidgetItem(QString(Time1String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Time2String = QString::number(myEmpData[row].time2);
         item = new QTableWidgetItem(QString(Time2String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C1String = QString::number(myEmpData[row].CA);
         item = new QTableWidgetItem(QString(C1String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C2String = QString::number(myEmpData[row].CB);
         item = new QTableWidgetItem(QString(C2String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C3String = QString::number(myEmpData[row].CC);
         item = new QTableWidgetItem(QString(C3String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C4String = QString::number(myEmpData[row].CE);
         item = new QTableWidgetItem(QString(C4String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString tString = QString::number(myEmpData[row].t);
         item = new QTableWidgetItem(QString(tString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString effectsString = QString::number(myEmpData[row].effects);
         item = new QTableWidgetItem(QString(effectsString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString formulaString = QString::number(myEmpData[row].formula);
         item = new QTableWidgetItem(QString(formulaString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString SortString = QString::number(myEmpData[row].sort);
         item = new QTableWidgetItem(QString(SortString));
         myDockRead->setTableItem(row,column,item);
        }

    else
        {
        QString formulaNumberString=QString::number(myLeaData[row].formulaNumber);
        QTableWidgetItem* item = new QTableWidgetItem(QString(formulaNumberString));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString Wavelenght1String=QString::number(myLeaData[row].wavelenght1);
        item = new QTableWidgetItem(QString(Wavelenght1String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString Wavelenght2String = QString::number(myLeaData[row].wavelenght2);
        item = new QTableWidgetItem(QString(Wavelenght2String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString Time1String = QString::number(myLeaData[row].time1);
        item = new QTableWidgetItem(QString(Time1String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString Time2String = QString::number(myLeaData[row].time2);
        item = new QTableWidgetItem(QString(Time2String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C1String = QString::number(myLeaData[row].C1);
        item = new QTableWidgetItem(QString(C1String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C2String = QString::number(myLeaData[row].C2);
        item = new QTableWidgetItem(QString(C2String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C3String = QString::number(myLeaData[row].C3);
        item = new QTableWidgetItem(QString(C3String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C4String = QString::number(myLeaData[row].C4);
        item = new QTableWidgetItem(QString(C4String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C5String = QString::number(myLeaData[row].C5);
        item = new QTableWidgetItem(QString(C5String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C6String = QString::number(myLeaData[row].C6);
        item = new QTableWidgetItem(QString(C6String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString C7String = QString::number(myLeaData[row].C7);
        item = new QTableWidgetItem(QString(C7String));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString tString = QString::number(myLeaData[row].t);
        item = new QTableWidgetItem(QString(tString));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString effectsString = QString::number(myLeaData[row].effects);
        item = new QTableWidgetItem(QString(effectsString));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString formulaString = QString::number(myLeaData[row].formula);
        item = new QTableWidgetItem(QString(formulaString));
        myDockRead->setTableItem(row,column,item);
        column++;

        QString SortString = QString::number(myLeaData[row].sort);
        item = new QTableWidgetItem(QString(SortString));
        myDockRead->setTableItem(row,column,item);
        }
    }
      //inVLEFile.close();
    QApplication::restoreOverrideCursor();

}

void MainWindow::writeBinarytable()
{
for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
 {
    int column=0;
    if(myBinaryData==EMP)
    {
           QString formulaNumberString=QString::number(myCodedEmpData[row].formulaNumber);
           QTableWidgetItem *item = new QTableWidgetItem(QString(formulaNumberString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Wavelength1String=QString::number(myCodedEmpData[row].wavelenght1);
           item = new QTableWidgetItem(QString(Wavelength1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Wavelength2String=QString::number(myCodedEmpData[row].wavelenght2);
           item = new QTableWidgetItem(QString(Wavelength2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Time1String=QString::number(myCodedEmpData[row].time1);
           item = new QTableWidgetItem(QString(Time1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Time2String=QString::number(myCodedEmpData[row].time2);
           item = new QTableWidgetItem(QString(Time2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C1String=QString::number(myCodedEmpData[row].CA);
           item = new QTableWidgetItem(QString(C1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C2String=QString::number(myCodedEmpData[row].CB);
           item = new QTableWidgetItem(QString(C2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C3String=QString::number(myCodedEmpData[row].CC);
           item = new QTableWidgetItem(QString(C3String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C4String=QString::number(myCodedEmpData[row].CE);
           item = new QTableWidgetItem(QString(C4String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString tString=QString::number(myCodedEmpData[row].t);
           item = new QTableWidgetItem(QString(tString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString effectsString=QString::number(myCodedEmpData[row].effects);
           item = new QTableWidgetItem(QString(effectsString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString formulaString=QString::number(myCodedEmpData[row].formula);
           item = new QTableWidgetItem(QString(formulaString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString SortString=QString::number(myCodedEmpData[row].sort);
           item = new QTableWidgetItem(QString(SortString));
           ui->binaryTable->setItem(row,column,item);
           column++;
          }
    else
        {
           QString formulaNumberString=QString::number(myCodedLeaData[row].formulaNumber);
           QTableWidgetItem *item = new QTableWidgetItem(QString(formulaNumberString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Wavelength1String=QString::number(myCodedLeaData[row].wavelenght1);
           item = new QTableWidgetItem(QString(Wavelength1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Wavelength2String=QString::number(myCodedLeaData[row].wavelenght2);
           item = new QTableWidgetItem(QString(Wavelength2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Time1String=QString::number(myCodedLeaData[row].time1);
           item = new QTableWidgetItem(QString(Time1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString Time2String=QString::number(myCodedLeaData[row].time2);
           item = new QTableWidgetItem(QString(Time2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C1String=QString::number(myCodedLeaData[row].C1);
           item = new QTableWidgetItem(QString(C1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C2String=QString::number(myCodedLeaData[row].C2);
           item = new QTableWidgetItem(QString(C2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C3String=QString::number(myCodedLeaData[row].C3);
           item = new QTableWidgetItem(QString(C3String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C4String=QString::number(myCodedLeaData[row].C4);
           item = new QTableWidgetItem(QString(C4String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C5String=QString::number(myCodedLeaData[row].C5);
           item = new QTableWidgetItem(QString(C5String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C6String=QString::number(myCodedLeaData[row].C6);
           item = new QTableWidgetItem(QString(C6String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString C7String=QString::number(myCodedLeaData[row].C7);
           item = new QTableWidgetItem(QString(C7String));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString tString=QString::number(myCodedLeaData[row].t);
           item = new QTableWidgetItem(QString(tString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString effectsString=QString::number(myCodedLeaData[row].effects);
           item = new QTableWidgetItem(QString(effectsString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString formulaString=QString::number(myCodedLeaData[row].formula);
           item = new QTableWidgetItem(QString(formulaString));
           ui->binaryTable->setItem(row,column,item);
           column++;

           QString SortString=QString::number(myCodedLeaData[row].sort);
           item = new QTableWidgetItem(QString(SortString));
           ui->binaryTable->setItem(row,column,item);
           column++;
          }
    }
}


void MainWindow::on_actionAggiorna_triggered()
{
    readAsciiTable();
    writeAsciiFile();
    writeAsciiTable();
    writeBinaryFile();
    readBinaryFile();
    writeBinarytable();
}

void MainWindow::setDataHeader()
{
    ui->binaryTable->setRowCount(maxRow[int(myBinaryData)]);

    QTableWidgetItem *item = new QTableWidgetItem("N");
    ui->binaryTable->setHorizontalHeaderItem(0,item);
    myDockRead->setTableHorizontalHeaderItem(0,item);
    item = new QTableWidgetItem("λ1");
    ui->binaryTable->setHorizontalHeaderItem(1,item);
    myDockRead->setTableHorizontalHeaderItem(1,item);
    item = new QTableWidgetItem("λ2");
    ui->binaryTable->setHorizontalHeaderItem(2,item);
    myDockRead->setTableHorizontalHeaderItem(2,item);
    item = new QTableWidgetItem("t1");
    ui->binaryTable->setHorizontalHeaderItem(3,item);
    myDockRead->setTableHorizontalHeaderItem(3,item);
    item = new QTableWidgetItem("t2");
    ui->binaryTable->setHorizontalHeaderItem(4,item);
    myDockRead->setTableHorizontalHeaderItem(4,item);

  if(EMP_Table){
    item = new QTableWidgetItem("CA");
    ui->binaryTable->setHorizontalHeaderItem(5,item);
    myDockRead->setTableHorizontalHeaderItem(5,item);
    item = new QTableWidgetItem("CB");
    ui->binaryTable->setHorizontalHeaderItem(6,item);
    myDockRead->setTableHorizontalHeaderItem(6,item);
    item = new QTableWidgetItem("CC");
    ui->binaryTable->setHorizontalHeaderItem(7,item);
    myDockRead->setTableHorizontalHeaderItem(7,item);
    item = new QTableWidgetItem("CE");
    ui->binaryTable->setHorizontalHeaderItem(8,item);
    myDockRead->setTableHorizontalHeaderItem(8,item);
    item = new QTableWidgetItem("t");
    ui->binaryTable->setHorizontalHeaderItem(9,item);
    myDockRead->setTableHorizontalHeaderItem(9,item);
    item = new QTableWidgetItem("effetti");
    ui->binaryTable->setHorizontalHeaderItem(10,item);
    myDockRead->setTableHorizontalHeaderItem(10,item);
    item = new QTableWidgetItem("formula");
    ui->binaryTable->setHorizontalHeaderItem(11,item);
    myDockRead->setTableHorizontalHeaderItem(11,item);
    item = new QTableWidgetItem("tipo");
    ui->binaryTable->setHorizontalHeaderItem(12,item);
    myDockRead->setTableHorizontalHeaderItem(12,item);

    item = new QTableWidgetItem("");
    myDockRead->setTableHorizontalHeaderItem(13,item);
    ui->binaryTable->setHorizontalHeaderItem(13,item);
    myDockRead->setTableHorizontalHeaderItem(14,item);
    ui->binaryTable->setHorizontalHeaderItem(14,item);
    myDockRead->setTableHorizontalHeaderItem(15,item);
    ui->binaryTable->setHorizontalHeaderItem(15,item);
  }
  else{
    item = new QTableWidgetItem("C1");
    ui->binaryTable->setHorizontalHeaderItem(5,item);
    myDockRead->setTableHorizontalHeaderItem(5,item);
    item = new QTableWidgetItem("C2");
    ui->binaryTable->setHorizontalHeaderItem(6,item);
    myDockRead->setTableHorizontalHeaderItem(6,item);
    item = new QTableWidgetItem("C3");
    ui->binaryTable->setHorizontalHeaderItem(7,item);
    myDockRead->setTableHorizontalHeaderItem(7,item);
    item = new QTableWidgetItem("C4");
    ui->binaryTable->setHorizontalHeaderItem(8,item);
    myDockRead->setTableHorizontalHeaderItem(8,item);
    item = new QTableWidgetItem("C5");
    ui->binaryTable->setHorizontalHeaderItem(9,item);
    myDockRead->setTableHorizontalHeaderItem(9,item);
    item = new QTableWidgetItem("C6");
    ui->binaryTable->setHorizontalHeaderItem(10,item);
    myDockRead->setTableHorizontalHeaderItem(10,item);
    item = new QTableWidgetItem("C7");
    ui->binaryTable->setHorizontalHeaderItem(11,item);
    myDockRead->setTableHorizontalHeaderItem(11,item);
    item = new QTableWidgetItem("t");
    ui->binaryTable->setHorizontalHeaderItem(12,item);
    myDockRead->setTableHorizontalHeaderItem(12,item);
    item = new QTableWidgetItem("effetti");
    ui->binaryTable->setHorizontalHeaderItem(13,item);
    myDockRead->setTableHorizontalHeaderItem(13,item);
    item = new QTableWidgetItem("formula");
    ui->binaryTable->setHorizontalHeaderItem(14,item);
    myDockRead->setTableHorizontalHeaderItem(14,item);
    item = new QTableWidgetItem("tipo");
    ui->binaryTable->setHorizontalHeaderItem(15,item);
    myDockRead->setTableHorizontalHeaderItem(15,item);
    }

}

void MainWindow::on_actionEMP_toggled(bool arg1)
{
    if(arg1){
         myBinaryData=EMP;
         myDockRead->setLabel("EMP");
         setInformation();
         updateData();
    }
}

void MainWindow::on_actionLEA_Classi_1_e_1M_toggled(bool arg1)
{
   if(arg1){
        myBinaryData=CLASSE_1_1M;
        myDockRead->setLabel("LEA Classe 1 e Classe 1M");
        setInformation();
        updateData();
   }
}

void MainWindow::on_actionLEA_Classe_3R_toggled(bool arg1)
{
    if(arg1){
        myBinaryData=CLASSE_3R;
        myDockRead->setLabel("LEA Classe 3R");
        setInformation();
        updateData();
    }
}

void MainWindow::on_actionLEA_Classe_3B_toggled(bool arg1)
{
    if(arg1){
        myBinaryData=CLASSE_3B;
        myDockRead->setLabel("LEA Classe 3B");
        setInformation();
        updateData();
    }
}

void MainWindow::updateData()
{
    ui->binaryTable->clear();
    myDockRead->clearAsciiDataTable();
    setDataHeader();

    readAsciiFile();
    writeAsciiFile();
    writeAsciiTable();   
    writeBinaryFile();
    readBinaryFile();
    writeBinarytable();
}

void MainWindow::on_actionTabella_ASCII_toggled(bool arg1)
{
   myDockRead->setVisible(arg1);
}

void MainWindow::setInformation()
{
if(myBinaryData==EMP){
       EMP_Table=true;
       filename="EMPdata.dat";
       binaryfilename ="EMPdataBinary.dat";
   }

else if(myBinaryData==CLASSE_1_1M){
        EMP_Table=false;
        filename="CLASSE_1_1M.dat";
        binaryfilename ="CLASSE_1_1M_dataBinary.dat";
   }

else if(myBinaryData==CLASSE_3R){
        EMP_Table=false;
        filename="CLASSE_3R.dat";
        binaryfilename ="CLASSE_3R_dataBinary.dat";
   }

else if(myBinaryData==CLASSE_3B){
        EMP_Table=false;
        filename="CLASSE_3B.dat";
        binaryfilename ="CLASSE_3B_dataBinary.dat";
   }
}

void MainWindow::printTables()
{
    html.clear();
    html ="<h1>"+ myDockRead->getLabel()+"</h1>\n"
          "<h2>Tabella ASCII</h2>\n"
            "<h3>Indicazione per la lettura</h3>\n"
            "<p>I Coefficienti C<sub>i</sub>, se presenti nella formula sono indicati con 1 altrimenti vi è uno 0. "
            "Il termine t invece se assente fa corrispondere 0, se del tipo t<sup>0,75</sup> fa corrispondere 1, "
            "se del tipo t<sup>0,25</sup> fa corrispondere 2, se del tipo t fa corrispondere 3. "
            "<p>Le cifre relative agli effetti codificano gli effetti su occhi e cute.</p>"
            "<ol><li>Radiazione: UV; occhio: danno fotochimico e danno termico;"
            "pelle: eritema.</li>"
            "<li> Radiazione: visibile; occhio : retina; pelle: danno termico.</li>"
            "<li> Radiazione: IRA; occhio: retina; pelle: danno termico.</li>"
            "<li> Radiazione: IRA; occhio: retina; pelle: danno termico.</li>"
            "<li> Radiazione: visibile; occhio: retina, danno fotochimico e danno termico; pelle: danno termico.</li>"
            "<li> Radiazione: visibile; occhio: retina; pelle: danno termico.</li>"
            "<li> Radiazione: IRB, IRC; occhio:	danno termico;	pelle: danno termico.</li></ol><br>"
            "La costante mostra il fattore in numero della formula.</p>"
            "<p>Il tipo considera la grandezza fisica:</p>"
            "<ol> <li>Irradianza</li>"
                " <li>Esposizione radiante</li>"
                " <li>Potenza</li>"
                " <li>Energia</li>"
            "</ol><br>"
           "<table width=\"100%\">\n"
                       "<tr><td>N</td>\n"
                       "<td>&#955;<sub>1</sub></td>\n"
                       "<td>&#955;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n";

    if(EMP_Table){
               html += "<td>C<sub>A</sub></td>\n"
                       "<td>C<sub>B</sub></td>\n"
                       "<td>C<sub>C</sub></td>\n"
                       "<td>C<sub>E</sub></td>\n"
                       "<td>t</td>\n"
                       "<td>Effetti</td>\n"
                       "<td>Coefficiente</td>\n"
                       "<td>tipo</td></td></tr>\n";
            }
            else
            {
                html += "<td>C<sub>1</sub></td>\n"
                        "<td>C<sub>2</sub></td>\n"
                        "<td>C<sub>3</sub></td>\n"
                        "<td>C<sub>4</sub></td>\n"
                        "<td>C<sub>5</sub></td>\n"
                        "<td>C<sub>6</sub></td>\n"
                        "<td>C<sub>7</sub></td>\n"
                        "<td>t</td>\n"
                        "<td>Effetti</td>\n"
                        "<td>Costante</td>\n"
                        "<td>tipo</td></td></tr>\n";
            }

for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
{
    if(EMP_Table){

     QString formulaNumberString=QString::number(myEmpData[row].formulaNumber);
     QString Wavelenght1String=QString::number(myEmpData[row].wavelenght1);
     QString Wavelenght2String=QString::number(myEmpData[row].wavelenght2);
     QString Time1String=QString::number(myEmpData[row].time1);
     QString Time2String=QString::number(myEmpData[row].time2);
     QString CAString=QString::number(myEmpData[row].CA);
     QString CBString=QString::number(myEmpData[row].CB);
     QString CCString=QString::number(myEmpData[row].CC);
     QString CEString=QString::number(myEmpData[row].CE);
     QString tString=QString::number(myEmpData[row].t);
     QString effects=QString::number(myEmpData[row].effects);
     QString formulaString=QString::number(myEmpData[row].formula);
     QString SortString=QString::number(myEmpData[row].sort);

     html +=
          "<tr><td>" +formulaNumberString+ "</td>\n"
          "<td>"+ Wavelenght1String +"</td>\n"
          "<td>"+ Wavelenght2String +"</td>\n"
          "<td>"+ Time1String +"</td>\n"
          "<td>"+ Time2String +"</td>\n"
          "<td>"+ CAString +"</td>\n"
          "<td>"+ CBString +"</td>\n"
          "<td>"+ CCString +"</td>\n"
          "<td>"+ CEString +"</td>\n"
          "<td>"+ tString +"</td>\n"
          "<td>"+ effects +"</td>\n"
          "<td>"+ formulaString +"</td>\n"
          "<td>"+ SortString +"</td></td></tr>\n";
     }
            else
 {
         QString formulaNumberString=QString::number(myLeaData[row].formulaNumber);
         QString Wavelenght1String=QString::number(myLeaData[row].wavelenght1);
         QString Wavelenght2String=QString::number(myLeaData[row].wavelenght2);
         QString Time1String=QString::number(myLeaData[row].time1);
         QString Time2String=QString::number(myLeaData[row].time2);
         QString C1String=QString::number(myLeaData[row].C1);
         QString C2String=QString::number(myLeaData[row].C2);
         QString C3String=QString::number(myLeaData[row].C3);
         QString C4String=QString::number(myLeaData[row].C4);
         QString C5String=QString::number(myLeaData[row].C5);
         QString C6String=QString::number(myLeaData[row].C6);
         QString C7String=QString::number(myLeaData[row].C7);
         QString tString=QString::number(myLeaData[row].t);
         QString effects=QString::number(myLeaData[row].effects);
         QString formulaString=QString::number(myLeaData[row].formula);
         QString SortString=QString::number(myLeaData[row].sort);

                html +=
                 "<tr><td>" +formulaNumberString+ "</td>\n"
                 "<td>"+ Wavelenght1String +"</td>\n"
                 "<td>"+ Wavelenght2String +"</td>\n"
                 "<td>"+ Time1String +"</td>\n"
                 "<td>"+ Time2String +"</td>\n"
                 "<td>"+ C1String +"</td>\n"
                 "<td>"+ C2String +"</td>\n"
                 "<td>"+ C3String +"</td>\n"
                 "<td>"+ C4String +"</td>\n"
                 "<td>"+ C5String +"</td>\n"
                 "<td>"+ C6String +"</td>\n"
                 "<td>"+ C7String +"</td>\n"
                 "<td>"+ tString +"</td>\n"
                 "<td>"+ effects +"</td>\n"
                 "<td>"+ formulaString +"</td>\n"
                 "<td>"+ SortString +"</td></td></tr>\n";
        }

    }

    html+= "</table><br>\n";

    html +="<br><br><h1>"+ myDockRead->getLabel()+"</h1>\n"
          "<h2>Tabella Binaria</h2>\n"
           "<table width=\"100%\">\n"
                       "<tr><td>N</td>\n"
                       "<td>&#955;<sub>1</sub></td>\n"
                       "<td>&#955;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n";
            if(EMP_Table){
               html += "<td>C<sub>A</sub></td>\n"
                       "<td>C<sub>B</sub></td>\n"
                       "<td>C<sub>C</sub></td>\n"
                       "<td>C<sub>E</sub></td>\n"
                       "<td>t</td>\n"
                       "<td>Effetti</td>\n"
                       "<td>Costante</td>\n"
                       "<td>tipo</td></td></tr>\n";
            }
            else
            {
                html += "<td>C<sub>1</sub></td>\n"
                        "<td>C<sub>2</sub></td>\n"
                        "<td>C<sub>3</sub></td>\n"
                        "<td>C<sub>4</sub></td>\n"
                        "<td>C<sub>5</sub></td>\n"
                        "<td>C<sub>6</sub></td>\n"
                        "<td>C<sub>7</sub></td>\n"
                        "<td>t</td>\n"
                        "<td>Effetti</td>\n"
                        "<td>Coefficiente</td>\n"
                        "<td>tipo</td></td></tr>\n";
            }

for(int row = 0; row<maxRow[int(myBinaryData)]; row++)
  {
  if(EMP_Table){
        QString formulaNumberString=QString::number(myCodedEmpData[row].formulaNumber);
        QString Wavelenght1String=QString::number(myCodedEmpData[row].wavelenght1);
        QString Wavelenght2String=QString::number(myCodedEmpData[row].wavelenght2);
        QString Time1String=QString::number(myCodedEmpData[row].time1);
        QString Time2String=QString::number(myCodedEmpData[row].time2);
        QString CAString=QString::number(myCodedEmpData[row].CA);
        QString CBString=QString::number(myCodedEmpData[row].CB);
        QString CCString=QString::number(myCodedEmpData[row].CC);
        QString CEString=QString::number(myCodedEmpData[row].CE);
        QString tString=QString::number(myCodedEmpData[row].t);
        QString effects=QString::number(myCodedEmpData[row].effects);
        QString formulaString=QString::number(myCodedEmpData[row].formula);
        QString SortString=QString::number(myCodedEmpData[row].sort);
        html +=
             "<tr><td>" +formulaNumberString+ "</td>\n"
             "<td>"+ Wavelenght1String +"</td>\n"
             "<td>"+ Wavelenght2String +"</td>\n"
             "<td>"+ Time1String +"</td>\n"
             "<td>"+ Time2String +"</td>\n"
             "<td>"+ CAString +"</td>\n"
             "<td>"+ CBString +"</td>\n"
             "<td>"+ CCString +"</td>\n"
             "<td>"+ CEString +"</td>\n"
             "<td>"+ tString +"</td>\n"
             "<td>"+ effects +"</td>\n"
             "<td>"+ formulaString +"</td>\n"
             "<td>"+ SortString +"</td></td></tr>\n";
        }
        else
        {
        QString formulaNumberString=QString::number(myCodedLeaData[row].formulaNumber);
        QString Wavelenght1String=QString::number(myCodedLeaData[row].wavelenght1);
        QString Wavelenght2String=QString::number(myCodedLeaData[row].wavelenght2);
        QString Time1String=QString::number(myCodedLeaData[row].time1);
        QString Time2String=QString::number(myCodedLeaData[row].time2);
        QString C1String=QString::number(myCodedLeaData[row].C1);
        QString C2String=QString::number(myCodedLeaData[row].C2);
        QString C3String=QString::number(myCodedLeaData[row].C3);
        QString C4String=QString::number(myCodedLeaData[row].C4);
        QString C5String=QString::number(myCodedLeaData[row].C5);
        QString C6String=QString::number(myCodedLeaData[row].C6);
        QString C7String=QString::number(myCodedLeaData[row].C7);
        QString tString=QString::number(myCodedLeaData[row].t);
        QString effects=QString::number(myCodedLeaData[row].effects);
        QString formulaString=QString::number(myCodedLeaData[row].formula);
        QString SortString=QString::number(myCodedLeaData[row].sort);

                html +=
                 "<tr><td>" +formulaNumberString+ "</td>\n"
                 "<td>"+ Wavelenght1String +"</td>\n"
                 "<td>"+ Wavelenght2String +"</td>\n"
                 "<td>"+ Time1String +"</td>\n"
                 "<td>"+ Time2String +"</td>\n"
                 "<td>"+ C1String +"</td>\n"
                 "<td>"+ C2String +"</td>\n"
                 "<td>"+ C3String +"</td>\n"
                 "<td>"+ C4String +"</td>\n"
                 "<td>"+ C5String +"</td>\n"
                 "<td>"+ C6String +"</td>\n"
                 "<td>"+ C7String +"</td>\n"
                 "<td>"+ tString +"</td>\n"
                 "<td>"+ effects +"</td>\n"
                 "<td>"+ formulaString +"</td>\n"
                 "<td>"+ SortString +"</td></td></tr>\n";
        }
    }
       html+= "</table><br>\n";

}

void MainWindow::on_actionStampa_triggered()
{
    QTextDocument document;
    printTables();

    QString headerAdjusted;

    headerAdjusted=QString("Esporta tabelle RAW %1")
                         .arg(adjustHeader());

    QString filename = QFileDialog::getSaveFileName(this, headerAdjusted,
                               "../Tabelle RAW.pdf",
                               tr("File pdf (*.pdf)"));

    if (!filename.isEmpty())
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);

        document.print(&printer);
        QApplication::restoreOverrideCursor();
    }
}

void MainWindow::on_actionInformazioni_su_Qt_triggered()
{
    qApp->aboutQt();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNumero_di_righe_triggered()
{
    RowDialog dialog(this, maxRow);
    dialog.exec();
    if(dialog.result()==QDialog::Accepted)
     {
      for(int row=0; row<maxRow[int(myBinaryData)]; row++)
        maxRow[row]=dialog.getMaxRowArray()[row];

       updateData();
     }
}

void MainWindow::on_actionInformazioni_triggered()
{
    QMessageBox::about(this, tr("Informazioni su Laser Studio"),
            tr("<h2>VL Table Editor</h2>"
               "<p>Applicazione per compilazione in file <br>"
               " binari delle Tabelle EMP e LEA.</p>"
               "<p>Autore: Ing. Carmine Giordano</p>"));
}

void MainWindow::on_actionLea_3R_60825_1_triggered()
{
    Table3RDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actiontabella_Lea_1_e_1M_triggered()
{
    Table1MDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionLea_3B_60825_1_triggered()
{
    Table3BDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionTabella_2_2_triggered()
{
    Table22Dialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionTabella_2_3_triggered()
{
    Table23Dialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionStampa_tabelleCompilate_triggered()
{
int classification;
QString html;

    if(myBinaryData==EMP)
        {
        myEMP_Print.writeEmpInStructValues();
        html=myEMP_Print.create_EMP_Table();
        }
        else if(myBinaryData==CLASSE_1_1M)
        {
        classification=0;
        myLEA_Print.writeLeaInStructValues((classData)classification);
        html=myLEA_Print.create_LEA_Table((classData)classification);
        }
        else if(myBinaryData==CLASSE_3R)
        {
        classification=2;
        myLEA_Print.writeLeaInStructValues((classData)classification);
        html=myLEA_Print.create_LEA_Table((classData)classification);
        }
        else if(myBinaryData==CLASSE_3B)
        {
        classification=3;
        myLEA_Print.writeLeaInStructValues((classData)classification);
        html=myLEA_Print.create_LEA_Table((classData)classification);
    }

    QTextDocument document;

    QString headerAdjusted;

    headerAdjusted=QString("Esporta la tabella compilata %1")
                         .arg(adjustHeader());

    QString filename = QFileDialog::getSaveFileName(this, headerAdjusted,
                                     "../Tabella valori.pdf",
                                        tr("File pdf (*.pdf)"));
    if (!filename.isEmpty())
        {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filename);
        document.print(&printer);
        QApplication::restoreOverrideCursor();
        }
}

void MainWindow::on_actionSalva_fiel_binario_triggered()
{
    QString headerAdjusted;

    headerAdjusted=QString("Salva file binario %1")
                         .arg(adjustHeader());

    QString filename = QFileDialog::getSaveFileName(this, headerAdjusted,
                                     "../binary.dat",
                                        tr("File binario (*.dat)"));
    if (!filename.isEmpty()){

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("VLE Table Editor"),
                             tr("Non è possibile salvare il file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return exit(1);
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    for(int row=0; row<maxRow[int(myBinaryData)]; row++) {
        if(EMP_Table){
            out << myEmpData[row].formulaNumber << myEmpData[row].wavelenght1 << myEmpData[row].wavelenght2
                << myEmpData[row].time1 << myEmpData[row].time2 << myEmpData[row].CA << myEmpData[row].CB
                << myEmpData[row].CC << myEmpData[row].CE << myEmpData[row].t << myEmpData[row].effects
                << myEmpData[row].formula << myEmpData[row].sort;
                }
        else
        {
            out << myLeaData[row].formulaNumber << myLeaData[row].wavelenght1 << myLeaData[row].wavelenght2
                << myLeaData[row].time1 << myLeaData[row].time2 << myLeaData[row].C1 << myLeaData[row].C2
                << myLeaData[row].C3 << myLeaData[row].C4 << myLeaData[row].C5 << myLeaData[row].C6
                << myLeaData[row].C7 << myLeaData[row].t << myLeaData[row].effects << myLeaData[row].formula
                << myLeaData[row].sort;
               }
          }
      QApplication::restoreOverrideCursor();
    }
}


QString MainWindow::adjustHeader()
{
    QString header;

    if(myBinaryData==EMP)
        header="EMP";
    else if(myBinaryData==CLASSE_1_1M)
        header="Classe 1 e 1M";
    else if(myBinaryData==CLASSE_3R)
        header="Classe 3R";
    else if(myBinaryData==CLASSE_3B)
        header="Classe 3R";

    return header;
}
