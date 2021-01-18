#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include "limitdata.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include "dockread.h"
#include "ui_dockread.h"

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

    QIcon iconWin;
    iconWin.addFile(QStringLiteral(":/images/ico.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(iconWin);

    maxRow=70;
    maxColumn=13;
    myBinaryData=EMP;
    EMP_Table=true;
    setDataHeader();
    readAsciiData();
    on_actionAggiorna_triggered();
}


/******************************************************************
 * Legge il file testo non codificato e codifica in file binario  *
 ******************************************************************/

void MainWindow::writeBinaryData()
{
 if(myBinaryData==EMP){
        maxRow=70;
        maxColumn=13;
        EMP_Table=true;
        binaryfilename="EMPdataBinary.dat";
    }

if(myBinaryData==CLASSE_1_1M){
         maxRow=42;
         maxColumn=16;
         EMP_Table=false;
         binaryfilename="CLASSE_1_1M_dataBinary.dat";
    }

if(myBinaryData==CLASSE_3R){
          maxRow=38;
          maxColumn=16;
          EMP_Table=false;
          binaryfilename="CLASSE_3R_dataBinary.dat";
    }

 QFile file(QString::fromStdString(binaryfilename));
 if (!file.open(QIODevice::WriteOnly)) {
     QMessageBox::warning(this, tr("Laser Safety"),
                          tr("Cannot write file %1:\n%2.")
                          .arg(file.fileName())
                          .arg(file.errorString()));
 }

 QDataStream out(&file);
 out.setVersion(QDataStream::Qt_4_3);

 QApplication::setOverrideCursor(Qt::WaitCursor);

         for(int row=0; row<maxRow; row++) {

              int column=0;

              myLimitData[row].formulaNumber=myDockRead->getTableItem(row, column)->text().toInt();
              column++;
              myLimitData[row].Wavelenght1=myDockRead->getTableItem(row,column)->text().toDouble();
              column++;
              myLimitData[row].Wavelenght2=myDockRead->getTableItem(row,column)->text().toDouble();
              column++;
              myLimitData[row].Time1=myDockRead->getTableItem(row,column)->text().toDouble();
              column++;
              myLimitData[row].Time2=myDockRead->getTableItem(row,column)->text().toDouble();
              column++;
              myLimitData[row].C1=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].C2=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].C3=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].C4=myDockRead->getTableItem(row,column)->text().toInt();
              column++;

              if(!EMP_Table){
              myLimitData[row].C5=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].C6=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].C7=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              }

              myLimitData[row].t=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].effects=myDockRead->getTableItem(row,column)->text().toInt();
              column++;
              myLimitData[row].formula=myDockRead->getTableItem(row,column)->text().toDouble();
              column++;
              myLimitData[row].Sort=myDockRead->getTableItem(row,column)->text().toInt();
    }

for(int row=0; row<maxRow; row++) {
    if(!EMP_Table){

              out << myLimitData[row].formulaNumber << myLimitData[row].Wavelenght1 << myLimitData[row].Wavelenght2
                  << myLimitData[row].Time1 << myLimitData[row].Time2 << myLimitData[row].C1 << myLimitData[row].C2
                  << myLimitData[row].C3 << myLimitData[row].C4 << myLimitData[row].C5 << myLimitData[row].C6
                  << myLimitData[row].C7 << myLimitData[row].t << myLimitData[row].effects << myLimitData[row].formula
                  << myLimitData[row].Sort;
            }
    else
    {
             out << myLimitData[row].formulaNumber << myLimitData[row].Wavelenght1 << myLimitData[row].Wavelenght2
                 << myLimitData[row].Time1 << myLimitData[row].Time2 << myLimitData[row].C1 << myLimitData[row].C2
                 << myLimitData[row].C3 << myLimitData[row].C4 << myLimitData[row].t << myLimitData[row].effects
                 << myLimitData[row].formula << myLimitData[row].Sort;
           }
   }
          QApplication::restoreOverrideCursor();
}

/**************************
 * Legge il file di testo *
 **************************/

void MainWindow::readAsciiData()
{
    if(myBinaryData==EMP){
        maxRow=70;
        maxColumn=13;
        EMP_Table=true;
        filename ="EMPdata.dat";
    }
    else
    if(myBinaryData==CLASSE_1_1M){

        maxRow=42;
        maxColumn=16;
        EMP_Table=false;
        filename ="CLASSE_1_1M.dat";
    }
    else
    if(myBinaryData==CLASSE_3R){
        maxRow=38;
        maxColumn=16;
        EMP_Table=false;
        filename ="CLASSE_3R.dat";
    }


// ifstream constructor opens the file
std::ifstream inVL_DataFile(filename, std::ios::in );

if ( !inVL_DataFile ) {
    std::cerr << "File could not be opened\n";
       exit( 1 );
}

for(int row = 0; row<maxRow; row++)
  {

  if(EMP_Table){
     inVL_DataFile >> myLimitData[row].formulaNumber >> myLimitData[row].Wavelenght1 >> myLimitData[row].Wavelenght2 >>
                  myLimitData[row].Time1 >> myLimitData[row].Time2 >> myLimitData[row].C1 >> myLimitData[row].C2 >>
                  myLimitData[row].C3 >> myLimitData[row].C4 >> myLimitData[row].t >> myLimitData[row].effects >>
                  myLimitData[row].formula >> myLimitData[row].Sort;}
            else{
     inVL_DataFile >> myLimitData[row].formulaNumber >> myLimitData[row].Wavelenght1 >> myLimitData[row].Wavelenght2 >>
                  myLimitData[row].Time1 >> myLimitData[row].Time2 >> myLimitData[row].C1 >> myLimitData[row].C2 >>
                  myLimitData[row].C3 >> myLimitData[row].C4 >> myLimitData[row].C5 >> myLimitData[row].C6 >>
                  myLimitData[row].C7 >> myLimitData[row].t >> myLimitData[row].effects >>
                  myLimitData[row].formula >> myLimitData[row].Sort;}
}

    for(int row = 0; row<maxRow; row++)
{
     int column=0;

         QString formulaNumberString=QString::number(myLimitData[row].formulaNumber);
         QTableWidgetItem* item = new QTableWidgetItem(QString(formulaNumberString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Wavelenght1String=QString::number(myLimitData[row].Wavelenght1);
         item = new QTableWidgetItem(QString(Wavelenght1String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Wavelenght2String = QString::number(myLimitData[row].Wavelenght2);
         item = new QTableWidgetItem(QString(Wavelenght2String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Time1String = QString::number(myLimitData[row].Time1);
         item = new QTableWidgetItem(QString(Time1String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString Time2String = QString::number(myLimitData[row].Time2);
         item = new QTableWidgetItem(QString(Time2String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C1String = QString::number(myLimitData[row].C1);
         item = new QTableWidgetItem(QString(C1String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C2String = QString::number(myLimitData[row].C2);
         item = new QTableWidgetItem(QString(C2String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C3String = QString::number(myLimitData[row].C3);
         item = new QTableWidgetItem(QString(C3String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C4String = QString::number(myLimitData[row].C4);
         item = new QTableWidgetItem(QString(C4String));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString C5String;
         QString C6String;
         QString C7String;

         if(!EMP_Table){
         C5String = QString::number(myLimitData[row].C5);
         item = new QTableWidgetItem(QString(C5String));
         myDockRead->setTableItem(row,column,item);
         column++;

         C6String = QString::number(myLimitData[row].C6);
         item = new QTableWidgetItem(QString(C6String));
         myDockRead->setTableItem(row,column,item);
         column++;

         C7String = QString::number(myLimitData[row].C7);
         item = new QTableWidgetItem(QString(C7String));
         myDockRead->setTableItem(row,column,item);
         column++;
        }

         QString tString = QString::number(myLimitData[row].t);
         item = new QTableWidgetItem(QString(tString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString effectsString = QString::number(myLimitData[row].effects);
         item = new QTableWidgetItem(QString(effectsString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString formulaString = QString::number(myLimitData[row].formula);
         item = new QTableWidgetItem(QString(formulaString));
         myDockRead->setTableItem(row,column,item);
         column++;

         QString SortString = QString::number(myLimitData[row].Sort);
         item = new QTableWidgetItem(QString(SortString));
         myDockRead->setTableItem(row,column,item);
    }

      //inVLEFile.close();
    QApplication::restoreOverrideCursor();

}

void MainWindow::on_actionAggiorna_triggered()
{
   writeBinaryData();

   if(myBinaryData==EMP){

       maxRow=70;
       maxColumn=13;
       EMP_Table=true;
       filename ="EMPdataBinary.dat";
   }

   if(myBinaryData==CLASSE_1_1M){

       maxRow=42;
       maxColumn=16;
       EMP_Table=false;
       filename ="CLASSE_1_1M_dataBinary.dat";
   }

   if(myBinaryData==CLASSE_3R){

       maxRow=38;
       maxColumn=16;
       EMP_Table=false;
       filename ="CLASSE_3R_dataBinary.dat";
   }

QFile file(QString::fromStdString(filename));
   if (!file.open(QIODevice::ReadOnly)) {
       QMessageBox::warning(this, tr("Laser Project"),
                            tr("Cannot read file %1:\n%2.")
                            .arg(file.fileName())
                            .arg(file.errorString()));
   }

   QDataStream in(&file);
   in.setVersion(QDataStream::Qt_4_3);

QApplication::setOverrideCursor(Qt::WaitCursor);

for(int row = 0; row<maxRow; row++)
 {
 if(EMP_Table){
        in >> myCodedLimitData[row].formulaNumber >> myCodedLimitData[row].Wavelenght1 >> myCodedLimitData[row].Wavelenght2 >>
              myCodedLimitData[row].Time1 >> myCodedLimitData[row].Time2 >> myCodedLimitData[row].C1 >> myCodedLimitData[row].C2 >>
              myCodedLimitData[row].C3 >> myCodedLimitData[row].C4 >> myCodedLimitData[row].t >> myCodedLimitData[row].effects >>
              myCodedLimitData[row].formula >> myCodedLimitData[row].Sort;

   qDebug()<< myCodedLimitData[row].formulaNumber << myCodedLimitData[row].Wavelenght1 << myCodedLimitData[row].Wavelenght2 <<
              myCodedLimitData[row].Time1 << myCodedLimitData[row].Time2 << myCodedLimitData[row].C1 << myCodedLimitData[row].C2 <<
              myCodedLimitData[row].C3 << myCodedLimitData[row].C4 << myCodedLimitData[row].t << myCodedLimitData[row].effects <<
              myCodedLimitData[row].formula << myCodedLimitData[row].Sort;}
    else {
        in >> myCodedLimitData[row].formulaNumber >> myCodedLimitData[row].Wavelenght1 >> myCodedLimitData[row].Wavelenght2 >>
              myCodedLimitData[row].Time1 >> myCodedLimitData[row].Time2 >> myCodedLimitData[row].C1 >> myCodedLimitData[row].C2 >>
              myCodedLimitData[row].C3 >> myCodedLimitData[row].C4 >> myCodedLimitData[row].C5 >> myCodedLimitData[row].C6 >>
              myCodedLimitData[row].C7 >> myCodedLimitData[row].t >> myCodedLimitData[row].effects >> myCodedLimitData[row].formula >>
              myCodedLimitData[row].Sort;

   qDebug()<< myCodedLimitData[row].formulaNumber << myCodedLimitData[row].Wavelenght1 << myCodedLimitData[row].Wavelenght2 <<
              myCodedLimitData[row].Time1 << myCodedLimitData[row].Time2 << myCodedLimitData[row].C1 << myCodedLimitData[row].C2 <<
              myCodedLimitData[row].C3 << myCodedLimitData[row].C4 << myCodedLimitData[row].C5 << myCodedLimitData[row].C6 <<
              myCodedLimitData[row].C7 << myCodedLimitData[row].t << myCodedLimitData[row].effects << myCodedLimitData[row].formula <<
              myCodedLimitData[row].Sort;}
}

for(int row = 0; row<maxRow; row++)
 {
   int column=0;
   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString formulaNumberString=QString::number(myCodedLimitData[row].formulaNumber);
           QTableWidgetItem *item = new QTableWidgetItem(QString(formulaNumberString));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString Wavelength1String=QString::number(myCodedLimitData[row].Wavelenght1);
           item = new QTableWidgetItem(QString(Wavelength1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString Wavelength2String=QString::number(myCodedLimitData[row].Wavelenght2);
           item = new QTableWidgetItem(QString(Wavelength2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString Time1String=QString::number(myCodedLimitData[row].Time1);
           item = new QTableWidgetItem(QString(Time1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString Time2String=QString::number(myCodedLimitData[row].Time2);
           item = new QTableWidgetItem(QString(Time2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C1String=QString::number(myCodedLimitData[row].C1);
           item = new QTableWidgetItem(QString(C1String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C2String=QString::number(myCodedLimitData[row].C2);
           item = new QTableWidgetItem(QString(C2String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C3String=QString::number(myCodedLimitData[row].C3);
           item = new QTableWidgetItem(QString(C3String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C4String=QString::number(myCodedLimitData[row].C4);
           item = new QTableWidgetItem(QString(C4String));
           ui->binaryTable->setItem(row,column,item);
           column++;

if(!EMP_Table){
   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C5String=QString::number(myCodedLimitData[row].C5);
           item = new QTableWidgetItem(QString(C5String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C6String=QString::number(myCodedLimitData[row].C6);
           item = new QTableWidgetItem(QString(C6String));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString C7String=QString::number(myCodedLimitData[row].C7);
           item = new QTableWidgetItem(QString(C7String));
           ui->binaryTable->setItem(row,column,item);
           column++;
    }

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString tString=QString::number(myCodedLimitData[row].t);
           item = new QTableWidgetItem(QString(tString));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString effectsString=QString::number(myCodedLimitData[row].effects);
           item = new QTableWidgetItem(QString(effectsString));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString formulaString=QString::number(myCodedLimitData[row].formula);
           item = new QTableWidgetItem(QString(formulaString));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Scrivo nelle cella..." << "Riga:"<< row << "Colonna "<< column;
           QString SortString=QString::number(myCodedLimitData[row].Sort);
           item = new QTableWidgetItem(QString(SortString));
           ui->binaryTable->setItem(row,column,item);
           column++;

   qDebug()<< "Verifica ondizione su row: ";
          }

QApplication::restoreOverrideCursor();
}

void MainWindow::setDataHeader()
{
    ui->binaryTable->setRowCount(maxRow);
        ui->binaryTable->setColumnCount(maxColumn);

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
    myDockRead->setTableHorizontalHeaderItem(14,item);
    myDockRead->setTableHorizontalHeaderItem(15,item);
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
/*
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==0){
        myBinaryData=EMP;
        maxRow=70;
        maxColumn=13;
        EMP_Table=true;
        }
            else if(index==1){
                myBinaryData=CLASSE_1_1M;
                maxRow=42;
                maxColumn=16;
                EMP_Table=false;
                }
                    else if(index==2){
                        myBinaryData=CLASSE_3R;
                        maxRow=38;
                        maxColumn=16;
                        EMP_Table=false;
                        }

    ui->binaryTable->clear();
    myDockRead->ui->asciiDataTable->clear();
    setDataHeader();
    readAsciiData();
    on_actionAggiorna_triggered();
}
*/
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEMP_toggled(bool arg1)
{
    if(arg1)
    {
            myBinaryData=EMP;
            maxRow=70;
            maxColumn=13;
            EMP_Table=true;
            myDockRead->setLabel("EMP");
            }
    updateData();
}

void MainWindow::on_actionLEA_Classi_1_e_1M_toggled(bool arg1)
{
   if(arg1){
        myBinaryData=CLASSE_1_1M;
        maxRow=42;
        maxColumn=16;
        EMP_Table=false;
        myDockRead->setLabel("LEA Classe 1 e Classe 1M");
        }
   updateData();
}

void MainWindow::on_actionLEA_Classe_3R_toggled(bool arg1)
{
    if(arg1){
        myBinaryData=CLASSE_3R;
        maxRow=38;
        maxColumn=16;
        EMP_Table=false;
        myDockRead->setLabel("LEA Classe 3R");
        }
    updateData();
}

void MainWindow::updateData()
{
    ui->binaryTable->clear();
    myDockRead->clearAsciiDataTable();
    setDataHeader();
    readAsciiData();
    on_actionAggiorna_triggered();
}

void MainWindow::on_actionTabella_ASCII_toggled(bool arg1)
{
   myDockRead->setVisible(arg1);
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

    for(int row = 0; row<maxRow; row++)
     {

    QString formulaNumberString=QString::number(myLimitData[row].formulaNumber);
    QString Wavelenght1String=QString::number(myLimitData[row].Wavelenght1);
    QString Wavelenght2String=QString::number(myLimitData[row].Wavelenght2);
    QString Time1String=QString::number(myLimitData[row].Time1);
    QString Time2String=QString::number(myLimitData[row].Time2);
    QString C1String=QString::number(myLimitData[row].C1);
    QString C2String=QString::number(myLimitData[row].C2);
    QString C3String=QString::number(myLimitData[row].C3);
    QString C4String=QString::number(myLimitData[row].C4);
    QString C5String=QString::number(myLimitData[row].C5);
    QString C6String=QString::number(myLimitData[row].C6);
    QString C7String=QString::number(myLimitData[row].C7);
    QString tString=QString::number(myLimitData[row].t);
    QString effects=QString::number(myLimitData[row].effects);
    QString formulaString=QString::number(myLimitData[row].formula);
    QString SortString=QString::number(myLimitData[row].Sort);


            if(EMP_Table){
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
                   "<td>"+ tString +"</td>\n"
                   "<td>"+ effects +"</td>\n"
                   "<td>"+ formulaString +"</td>\n"
                   "<td>"+ SortString +"</td></td></tr>\n";}
            else
            {
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

    for(int row = 0; row<maxRow; row++)
     {

        QString formulaNumberString=QString::number(myCodedLimitData[row].formulaNumber);
    QString Wavelenght1String=QString::number(myCodedLimitData[row].Wavelenght1);
    QString Wavelenght2String=QString::number(myCodedLimitData[row].Wavelenght2);
    QString Time1String=QString::number(myCodedLimitData[row].Time1);
    QString Time2String=QString::number(myCodedLimitData[row].Time2);
    QString C1String=QString::number(myCodedLimitData[row].C1);
    QString C2String=QString::number(myCodedLimitData[row].C2);
    QString C3String=QString::number(myCodedLimitData[row].C3);
    QString C4String=QString::number(myCodedLimitData[row].C4);
    QString C5String=QString::number(myCodedLimitData[row].C5);
    QString C6String=QString::number(myCodedLimitData[row].C6);
    QString C7String=QString::number(myCodedLimitData[row].C7);
    QString tString=QString::number(myCodedLimitData[row].t);
    QString effects=QString::number(myCodedLimitData[row].effects);
    QString formulaString=QString::number(myCodedLimitData[row].formula);
    QString SortString=QString::number(myCodedLimitData[row].Sort);


            if(EMP_Table){
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
                   "<td>"+ tString +"</td>\n"
                   "<td>"+ effects +"</td>\n"
                   "<td>"+ formulaString +"</td>\n"
                   "<td>"+ SortString +"</td></td></tr>\n";}
            else
            {
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

}

void MainWindow::printReport(QPrinter *printer)
{
    #if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)

        printTables();

        QTextDocument textDocument;
        textDocument.setHtml(html);

        textDocument.print(printer);

    #endif
}


void MainWindow::on_actionStampa_triggered()
{
        QPrinter printer(QPrinter::HighResolution);
        printer.setPageMargins(QMarginsF(5, 5, 5, 5));
        QPrintDialog dialog(&printer, this);
        if (dialog.exec() != QDialog::Accepted)
            return;

        printReport(&printer);
}

void MainWindow::on_actionInformazioni_su_Qt_triggered()
{
    qApp->aboutQt();
}
