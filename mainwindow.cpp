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
    ui(new Ui::MainWindow),wavelength(633), time(0.25), myLeaData{}, myEmpData{}, myCodedLeaData{}, myCodedEmpData{}
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

    readAsciiFile();
    writeAsciiTable();
    writeBinaryFile();
    readBinaryFile();
    writeBinarytable();
}

void MainWindow::readAsciiTable()
{
for(int row=0; row<maxRow.at((int)myBinaryData); row++) {
    int column=0;

    if(myBinaryData==EMP)
{
    myEmpData.at(row).formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
    column++;
    myEmpData.at(row).wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData.at(row).wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData.at(row).time1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData.at(row).time2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData.at(row).CA=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData.at(row).CB=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData.at(row).CC=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData.at(row).CE=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData.at(row).t=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData.at(row).effects=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myEmpData.at(row).formula=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myEmpData.at(row).sort=myDockRead->getTableItem(row,column)->text().toInt();
    }
    else
    {
     myLeaData.at(row).formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
     column++;
     myLeaData.at(row).wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData.at(row).wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData.at(row).time1=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData.at(row).time2=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData.at(row).C1=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).C2=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).C3=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).C4=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).C5=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).C6=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).C7=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).t=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).effects=myDockRead->getTableItem(row,column)->text().toInt();
     column++;
     myLeaData.at(row).formula=myDockRead->getTableItem(row,column)->text().toDouble();
     column++;
     myLeaData.at(row).sort=myDockRead->getTableItem(row,column)->text().toInt();
    }
    }
}
void MainWindow::readBinaryTable()
{
for(int row=0; row<maxRow.at((int)myBinaryData); row++) {
  int column=0;
    if(myBinaryData==EMP)
{
    myCodedEmpData.at(row).formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
    column++;
    myCodedEmpData.at(row).wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData.at(row).wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData.at(row).time1=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData.at(row).time2=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData.at(row).CA=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData.at(row).CB=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData.at(row).CC=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData.at(row).CE=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData.at(row).t=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData.at(row).effects=myDockRead->getTableItem(row,column)->text().toInt();
    column++;
    myCodedEmpData.at(row).formula=myDockRead->getTableItem(row,column)->text().toDouble();
    column++;
    myCodedEmpData.at(row).sort=myDockRead->getTableItem(row,column)->text().toInt();
    }
    else
    {
     myCodedLeaData.at(row).formulaNumber=ui->binaryTable->item(row, column)->text().toInt();
     column++;
     myCodedLeaData.at(row).wavelenght1=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData.at(row).wavelenght2=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData.at(row).time1=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData.at(row).time2=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData.at(row).C1=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).C2=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).C3=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).C4=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).C5=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).C6=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).C7=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).t=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).effects=ui->binaryTable->item(row,column)->text().toInt();
     column++;
     myCodedLeaData.at(row).formula=ui->binaryTable->item(row,column)->text().toDouble();
     column++;
     myCodedLeaData.at(row).sort=ui->binaryTable->item(row,column)->text().toInt();
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

     for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
       {

       if(EMP_Table){
          outVL_DataFile << myEmpData.at(row).formulaNumber << " " << myEmpData.at(row).wavelenght1 << " " << myEmpData.at(row).wavelenght2 << " " <<
                       myEmpData.at(row).time1 << " " << myEmpData.at(row).time2 << " " << myEmpData.at(row).CA << " " << myEmpData.at(row).CB << " " <<
                       myEmpData.at(row).CC << " " << myEmpData.at(row).CE << " " << myEmpData.at(row).t << " " <<  myEmpData.at(row).effects << " " <<
                       myEmpData.at(row).formula << " " << myEmpData.at(row).sort <<" \n";}
       else{
          outVL_DataFile << myLeaData.at(row).formulaNumber << " " << myLeaData.at(row).wavelenght1 << " " << myLeaData.at(row).wavelenght2 << " " <<
                       myLeaData.at(row).time1 << " " << myLeaData.at(row).time2 << " " << myLeaData.at(row).C1 << " " << myLeaData.at(row).C2 << " " <<
                       myLeaData.at(row).C3 << " " << myLeaData.at(row).C4 << " " << myLeaData.at(row).C5 << " " << myLeaData.at(row).C6 << " " <<
                       myLeaData.at(row).C7 << " " << myLeaData.at(row).t << " " << myLeaData.at(row).effects << " " <<
                       myLeaData.at(row).formula << " " << myLeaData.at(row).sort <<" \n";}
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

for(int row=0; row<maxRow.at((int)myBinaryData); row++) {
    if(EMP_Table){
        out << myEmpData.at(row).formulaNumber << myEmpData.at(row).wavelenght1 << myEmpData.at(row).wavelenght2
            << myEmpData.at(row).time1 << myEmpData.at(row).time2 << myEmpData.at(row).CA << myEmpData.at(row).CB
            << myEmpData.at(row).CC << myEmpData.at(row).CE << myEmpData.at(row).t << myEmpData.at(row).effects
            << myEmpData.at(row).formula << myEmpData.at(row).sort;
            }
    else
    {    
        out << myLeaData.at(row).formulaNumber << myLeaData.at(row).wavelenght1 << myLeaData.at(row).wavelenght2
            << myLeaData.at(row).time1 << myLeaData.at(row).time2 << myLeaData.at(row).C1 << myLeaData.at(row).C2
            << myLeaData.at(row).C3 << myLeaData.at(row).C4 << myLeaData.at(row).C5 << myLeaData.at(row).C6
            << myLeaData.at(row).C7 << myLeaData.at(row).t << myLeaData.at(row).effects << myLeaData.at(row).formula
            << myLeaData.at(row).sort;
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

for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
  {

  if(EMP_Table){
     inVL_DataFile >> myEmpData.at(row).formulaNumber >> myEmpData.at(row).wavelenght1 >> myEmpData.at(row).wavelenght2 >>
                  myEmpData.at(row).time1 >> myEmpData.at(row).time2 >> myEmpData.at(row).CA >> myEmpData.at(row).CB >>
                  myEmpData.at(row).CC >> myEmpData.at(row).CE >> myEmpData.at(row).t >> myEmpData.at(row).effects >>
                  myEmpData.at(row).formula >> myEmpData.at(row).sort;}
  else{
     inVL_DataFile >> myLeaData.at(row).formulaNumber >> myLeaData.at(row).wavelenght1 >> myLeaData.at(row).wavelenght2 >>
                  myLeaData.at(row).time1 >> myLeaData.at(row).time2 >> myLeaData.at(row).C1 >> myLeaData.at(row).C2 >>
                  myLeaData.at(row).C3 >> myLeaData.at(row).C4 >> myLeaData.at(row).C5 >> myLeaData.at(row).C6 >>
                  myLeaData.at(row).C7 >> myLeaData.at(row).t >> myLeaData.at(row).effects >>
                  myLeaData.at(row).formula >> myLeaData.at(row).sort;}
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

        for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
         {
         if(EMP_Table){
                in >> myCodedEmpData.at(row).formulaNumber >> myCodedEmpData.at(row).wavelenght1 >> myCodedEmpData.at(row).wavelenght2 >>
                      myCodedEmpData.at(row).time1 >> myCodedEmpData.at(row).time2 >> myCodedEmpData.at(row).CA >> myCodedEmpData.at(row).CB >>
                      myCodedEmpData.at(row).CC >> myCodedEmpData.at(row).CE >> myCodedEmpData.at(row).t >> myCodedEmpData.at(row).effects >>
                      myCodedEmpData.at(row).formula >> myCodedEmpData.at(row).sort;
                      }
         else {
                in >> myCodedLeaData.at(row).formulaNumber >> myCodedLeaData.at(row).wavelenght1 >> myCodedLeaData.at(row).wavelenght2 >>
                      myCodedLeaData.at(row).time1 >> myCodedLeaData.at(row).time2 >> myCodedLeaData.at(row).C1 >> myCodedLeaData.at(row).C2 >>
                      myCodedLeaData.at(row).C3 >> myCodedLeaData.at(row).C4 >> myCodedLeaData.at(row).C5 >> myCodedLeaData.at(row).C6 >>
                      myCodedLeaData.at(row).C7 >> myCodedLeaData.at(row).t >> myCodedLeaData.at(row).effects >> myCodedLeaData.at(row).formula >>
                      myCodedLeaData.at(row).sort;
                      }
            }
}

void MainWindow::writeAsciiTable()
{
    for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
    {
    int column=0;
    if(myBinaryData==EMP)
    {
         QString formulaNumberString=QString::number(myEmpData.at(row).formulaNumber);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(formulaNumberString)));
         column++;

         QString Wavelenght1String=QString::number(myEmpData.at(row).wavelenght1);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Wavelenght1String)));
         column++;

         QString Wavelenght2String = QString::number(myEmpData.at(row).wavelenght2);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Wavelenght2String)));
         column++;

         QString Time1String = QString::number(myEmpData.at(row).time1);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Time1String)));
         column++;

         QString Time2String = QString::number(myEmpData.at(row).time2);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Time2String)));
         column++;

         QString C1String = QString::number(myEmpData.at(row).CA);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C1String)));
         column++;

         QString C2String = QString::number(myEmpData.at(row).CB);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C2String)));
         column++;

         QString C3String = QString::number(myEmpData.at(row).CC);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C3String)));
         column++;

         QString C4String = QString::number(myEmpData.at(row).CE);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C4String)));
         column++;

         QString tString = QString::number(myEmpData.at(row).t);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(tString)));
         column++;

         QString effectsString = QString::number(myEmpData.at(row).effects);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(effectsString)));
         column++;

         QString formulaString = QString::number(myEmpData.at(row).formula);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(formulaString)));
         column++;

         QString SortString = QString::number(myEmpData.at(row).sort);
         myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(SortString)));
        }

    else
        {
        QString formulaNumberString=QString::number(myLeaData.at(row).formulaNumber);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(formulaNumberString)));
        column++;

        QString Wavelenght1String=QString::number(myLeaData.at(row).wavelenght1);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Wavelenght1String)));
        column++;

        QString Wavelenght2String = QString::number(myLeaData.at(row).wavelenght2);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Wavelenght2String)));
        column++;

        QString Time1String = QString::number(myLeaData.at(row).time1);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Time1String)));
        column++;

        QString Time2String = QString::number(myLeaData.at(row).time2);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(Time2String)));
        column++;

        QString C1String = QString::number(myLeaData.at(row).C1);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C1String)));
        column++;

        QString C2String = QString::number(myLeaData.at(row).C2);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C2String)));
        column++;

        QString C3String = QString::number(myLeaData.at(row).C3);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C3String)));
        column++;

        QString C4String = QString::number(myLeaData.at(row).C4);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C4String)));
        column++;

        QString C5String = QString::number(myLeaData.at(row).C5);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C5String)));
        column++;

        QString C6String = QString::number(myLeaData.at(row).C6);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C6String)));
        column++;

        QString C7String = QString::number(myLeaData.at(row).C7);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(C7String)));
        column++;

        QString tString = QString::number(myLeaData.at(row).t);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(tString)));
        column++;

        QString effectsString = QString::number(myLeaData.at(row).effects);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(effectsString)));
        column++;

        QString formulaString = QString::number(myLeaData.at(row).formula);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(formulaString)));
        column++;

        QString SortString = QString::number(myLeaData.at(row).sort);
        myDockRead->setTableItem(row,column, new QTableWidgetItem(QString(SortString)));
        }
    }
      //inVLEFile.close();
    QApplication::restoreOverrideCursor();

}

void MainWindow::writeBinarytable()
{
for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
 {
    int column=0;
    if(myBinaryData==EMP)
    {
           QString formulaNumberString=QString::number(myCodedEmpData.at(row).formulaNumber);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(formulaNumberString)));
           column++;

           QString Wavelength1String=QString::number(myCodedEmpData.at(row).wavelenght1);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Wavelength1String)));
           column++;

           QString Wavelength2String=QString::number(myCodedEmpData.at(row).wavelenght2);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Wavelength2String)));
           column++;

           QString Time1String=QString::number(myCodedEmpData.at(row).time1);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Time1String)));
           column++;

           QString Time2String=QString::number(myCodedEmpData.at(row).time2);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Time2String)));
           column++;

           QString C1String=QString::number(myCodedEmpData.at(row).CA);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C1String)));
           column++;

           QString C2String=QString::number(myCodedEmpData.at(row).CB);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C2String)));
           column++;

           QString C3String=QString::number(myCodedEmpData.at(row).CC);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C3String)));
           column++;

           QString C4String=QString::number(myCodedEmpData.at(row).CE);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C4String)));
           column++;

           QString tString=QString::number(myCodedEmpData.at(row).t);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(tString)));
           column++;

           QString effectsString=QString::number(myCodedEmpData.at(row).effects);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(effectsString)));
           column++;

           QString formulaString=QString::number(myCodedEmpData.at(row).formula);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(formulaString)));
           column++;

           QString SortString=QString::number(myCodedEmpData.at(row).sort);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(SortString)));
           column++;
          }
    else
          {
           QString formulaNumberString=QString::number(myCodedLeaData.at(row).formulaNumber);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(formulaNumberString)));
           column++;

           QString Wavelength1String=QString::number(myCodedLeaData.at(row).wavelenght1);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Wavelength1String)));
           column++;

           QString Wavelength2String=QString::number(myCodedLeaData.at(row).wavelenght2);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Wavelength2String)));
           column++;

           QString Time1String=QString::number(myCodedLeaData.at(row).time1);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Time1String)));
           column++;

           QString Time2String=QString::number(myCodedLeaData.at(row).time2);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(Time2String)));
           column++;

           QString C1String=QString::number(myCodedLeaData.at(row).C1);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C1String)));
           column++;

           QString C2String=QString::number(myCodedLeaData.at(row).C2);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C2String)));
           column++;

           QString C3String=QString::number(myCodedLeaData.at(row).C3);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C3String)));
           column++;

           QString C4String=QString::number(myCodedLeaData.at(row).C4);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C4String)));
           column++;

           QString C5String=QString::number(myCodedLeaData.at(row).C5);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C5String)));
           column++;

           QString C6String=QString::number(myCodedLeaData.at(row).C6);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C6String)));
           column++;

           QString C7String=QString::number(myCodedLeaData.at(row).C7);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(C7String)));
           column++;

           QString tString=QString::number(myCodedLeaData.at(row).t);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(tString)));
           column++;

           QString effectsString=QString::number(myCodedLeaData.at(row).effects);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(effectsString)));
           column++;

           QString formulaString=QString::number(myCodedLeaData.at(row).formula);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(formulaString)));
           column++;

           QString SortString=QString::number(myCodedLeaData.at(row).sort);
           ui->binaryTable->setItem(row,column, new QTableWidgetItem(QString(SortString)));
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
    ui->binaryTable->setRowCount(maxRow.at((int)myBinaryData));

    QStringList m_TableHeader;
    if(EMP_Table){
    m_TableHeader<<"N"<<"λ1"<<"λ2"<<"t1"<<"t2"<<"CA"<<"CB"<<"CC"<<"CE"
                <<"t"<<"Effetti"<<"Formula"<<"Tipo"<<""<<""<<"";
    ui->binaryTable->setHorizontalHeaderLabels(m_TableHeader);
    myDockRead->setTableHorizontalHeaderLabels(m_TableHeader);
    }
    else
    {
    m_TableHeader<<"N"<<"λ1"<<"λ2"<<"t1"<<"t2"<<"C1"<<"C2"<<"C3"<<"C4"<<"C5"
                    <<"C6"<<"C7"<<"t"<<"Effetti"<<"Formula"<<"Tipo"<<""<<""<<"";
    ui->binaryTable->setHorizontalHeaderLabels(m_TableHeader);
    myDockRead->setTableHorizontalHeaderLabels(m_TableHeader);
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
            "</ol>"
           "<p>I risultati a cui corrispondono valori multipli non vengono considerati essendo gestiti dal software.</p><br>"
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
    else{
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

for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
{
    if(EMP_Table){

     QString formulaNumberString=QString::number(myEmpData.at(row).formulaNumber);
     QString Wavelenght1String=QString::number(myEmpData.at(row).wavelenght1);
     QString Wavelenght2String=QString::number(myEmpData.at(row).wavelenght2);
     QString Time1String=QString::number(myEmpData.at(row).time1);
     QString Time2String=QString::number(myEmpData.at(row).time2);
     QString CAString=QString::number(myEmpData.at(row).CA);
     QString CBString=QString::number(myEmpData.at(row).CB);
     QString CCString=QString::number(myEmpData.at(row).CC);
     QString CEString=QString::number(myEmpData.at(row).CE);
     QString tString=QString::number(myEmpData.at(row).t);
     QString effects=QString::number(myEmpData.at(row).effects);
     QString formulaString=QString::number(myEmpData.at(row).formula);
     QString SortString=QString::number(myEmpData.at(row).sort);

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
          "<td>"+ SortString +"</td></td></tr>\n";}
    else{
         QString formulaNumberString=QString::number(myLeaData.at(row).formulaNumber);
         QString Wavelenght1String=QString::number(myLeaData.at(row).wavelenght1);
         QString Wavelenght2String=QString::number(myLeaData.at(row).wavelenght2);
         QString Time1String=QString::number(myLeaData.at(row).time1);
         QString Time2String=QString::number(myLeaData.at(row).time2);
         QString C1String=QString::number(myLeaData.at(row).C1);
         QString C2String=QString::number(myLeaData.at(row).C2);
         QString C3String=QString::number(myLeaData.at(row).C3);
         QString C4String=QString::number(myLeaData.at(row).C4);
         QString C5String=QString::number(myLeaData.at(row).C5);
         QString C6String=QString::number(myLeaData.at(row).C6);
         QString C7String=QString::number(myLeaData.at(row).C7);
         QString tString=QString::number(myLeaData.at(row).t);
         QString effects=QString::number(myLeaData.at(row).effects);
         QString formulaString=QString::number(myLeaData.at(row).formula);
         QString SortString=QString::number(myLeaData.at(row).sort);

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
                 "<td>"+ SortString +"</td></td></tr>\n";}

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

for(int row = 0; row<maxRow.at((int)myBinaryData); row++)
  {
    if(EMP_Table){
        QString formulaNumberString=QString::number(myCodedEmpData.at(row).formulaNumber);
        QString Wavelenght1String=QString::number(myCodedEmpData.at(row).wavelenght1);
        QString Wavelenght2String=QString::number(myCodedEmpData.at(row).wavelenght2);
        QString Time1String=QString::number(myCodedEmpData.at(row).time1);
        QString Time2String=QString::number(myCodedEmpData.at(row).time2);
        QString CAString=QString::number(myCodedEmpData.at(row).CA);
        QString CBString=QString::number(myCodedEmpData.at(row).CB);
        QString CCString=QString::number(myCodedEmpData.at(row).CC);
        QString CEString=QString::number(myCodedEmpData.at(row).CE);
        QString tString=QString::number(myCodedEmpData.at(row).t);
        QString effects=QString::number(myCodedEmpData.at(row).effects);
        QString formulaString=QString::number(myCodedEmpData.at(row).formula);
        QString SortString=QString::number(myCodedEmpData.at(row).sort);
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
        QString formulaNumberString=QString::number(myCodedLeaData.at(row).formulaNumber);
        QString Wavelenght1String=QString::number(myCodedLeaData.at(row).wavelenght1);
        QString Wavelenght2String=QString::number(myCodedLeaData.at(row).wavelenght2);
        QString Time1String=QString::number(myCodedLeaData.at(row).time1);
        QString Time2String=QString::number(myCodedLeaData.at(row).time2);
        QString C1String=QString::number(myCodedLeaData.at(row).C1);
        QString C2String=QString::number(myCodedLeaData.at(row).C2);
        QString C3String=QString::number(myCodedLeaData.at(row).C3);
        QString C4String=QString::number(myCodedLeaData.at(row).C4);
        QString C5String=QString::number(myCodedLeaData.at(row).C5);
        QString C6String=QString::number(myCodedLeaData.at(row).C6);
        QString C7String=QString::number(myCodedLeaData.at(row).C7);
        QString tString=QString::number(myCodedLeaData.at(row).t);
        QString effects=QString::number(myCodedLeaData.at(row).effects);
        QString formulaString=QString::number(myCodedLeaData.at(row).formula);
        QString SortString=QString::number(myCodedLeaData.at(row).sort);

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
       std::array<int, 4> myMaxRow=dialog.getMaxRowArray();
       copy(myMaxRow.begin(), myMaxRow.end(), maxRow.begin());
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
        html=myLEA_Print.create_LEA_Table_1M();
        }
    else if(myBinaryData==CLASSE_3R)
        {
        classification=2;
        myLEA_Print.writeLeaInStructValues((classData)classification);
        html=myLEA_Print.create_LEA_Table_3R();
        }
    else if(myBinaryData==CLASSE_3B)
        {
        classification=3;
        myLEA_Print.writeLeaInStructValues((classData)classification);
        html=myLEA_Print.create_LEA_Table_3B();
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


    for(int row = 0; row<(maxRow.at((int)myBinaryData)); row++)
    {
        if(EMP_Table){
            out << myEmpData.at(row).formulaNumber << myEmpData.at(row).wavelenght1 << myEmpData.at(row).wavelenght2
                << myEmpData.at(row).time1 << myEmpData.at(row).time2 << myEmpData.at(row).CA << myEmpData.at(row).CB
                << myEmpData.at(row).CC << myEmpData.at(row).CE << myEmpData.at(row).t << myEmpData.at(row).effects
                << myEmpData.at(row).formula << myEmpData.at(row).sort;
                }
        else
        {
            out << myLeaData.at(row).formulaNumber << myLeaData.at(row).wavelenght1 << myLeaData.at(row).wavelenght2
                << myLeaData.at(row).time1 << myLeaData.at(row).time2 << myLeaData.at(row).C1 << myLeaData.at(row).C2
                << myLeaData.at(row).C3 << myLeaData.at(row).C4 << myLeaData.at(row).C5 << myLeaData.at(row).C6
                << myLeaData.at(row).C7 << myLeaData.at(row).t << myLeaData.at(row).effects << myLeaData.at(row).formula
                << myLeaData.at(row).sort;
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

void MainWindow::on_actionEsci_triggered()
{
    this->close();
}
