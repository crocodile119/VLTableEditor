#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <string>
#include "limitdata.h"
#include "dockread.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#endif

#include <QPrinter>
#include <QPrintDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readAsciiTable(); //Legge la tabella ascii e memorizzo nalla struttura myLimitData[70]
    void readBinaryTable(); //Legge la tabella binaria e memorizzo nalla struttura myCodedLimitData[70]

    void writeAsciiTable(); // scrivo la tabella ascii con i dati contenuti nella struttura myLimitData[70]
    void writeBinarytable(); // scrivo la tabella binaria con i dati contenuti nella struttura myCodedLimitData[70]

    void writeBinaryFile(); //Scrivo il file binario con i dati contenuti nalla struttura myLimitData[70]
    void writeAsciiFile(); //Scrivo il file ascii con i dati contenuti nalla struttura myCodedLimitData[70]

    void readAsciiFile(); //Legge il file ascii e li memorizza nalla nella tabella Ascii
    void readBinaryFile(); //Legge il file binario e li memorizza nalla struttura myCodedLimitData[70]

    void setInformation(); //imposta le informazioni

    void setDataHeader();
    void updateData();
    void printTables();
    void printReport(QPrinter *printer);


private slots:
    void on_actionAggiorna_triggered();
    void on_actionEMP_toggled(bool arg1);
    void on_actionLEA_Classi_1_e_1M_toggled(bool arg1);
    void on_actionLEA_Classe_3R_toggled(bool arg1);
    void on_actionTabella_ASCII_toggled(bool arg1);
    void on_actionStampa_triggered();
    void on_actionInformazioni_su_Qt_triggered();
    void on_actionNumero_di_righe_triggered();
    void on_actionInformazioni_triggered();

    void on_actionLEA_Classe_3B_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    double wavelength;
    double time;
    enum binaryData{EMP, CLASSE_1_1M, CLASSE_3R, CLASSE_3B};
    binaryData myBinaryData;
    int maxRow[4]={70, 42, 38, 21};
    bool EMP_Table;
    QString html;
    limitdata myLimitData[70];
    limitdata myCodedLimitData[70];

    std::string filename;
    std::string binaryfilename;
    DockRead *myDockRead;

    QActionGroup *tableGroup;
};

#endif // MAINWINDOW_H


