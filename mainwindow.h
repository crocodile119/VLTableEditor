#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <string>
#include "empdata.h"
#include "leadata.h"
#include "computeemp.h"
#include "computelea.h"
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
    void on_actionLea_3R_60825_1_triggered();

    void on_actiontabella_Lea_1_e_1M_triggered();
    void on_actionLea_3B_60825_1_triggered();
    void on_actionTabella_2_2_triggered();
    void on_actionTabella_2_3_triggered();
    void on_actionStampa_tabelleCompilate_triggered();

    void on_actionSalva_fiel_binario_triggered();

    QString adjustHeader();

    void on_actionEsci_triggered();

private:
    Ui::MainWindow *ui;
    double wavelength;
    double time;
    enum binaryData{EMP, CLASSE_1_1M, CLASSE_3R, CLASSE_3B};
    binaryData myBinaryData;
    std::array<int, 4>maxRow={70, 41, 38, 21};
    bool EMP_Table;
    QString html;
    std::array<leadata,70>myLeaData;
    std::array<empdata, 70> myEmpData;
    std::array<leadata,70> myCodedLeaData;
    std::array<empdata, 70> myCodedEmpData;
    ComputeLEA myLEA_Print;
    ComputeEMP myEMP_Print;

    std::string filename;
    std::string binaryfilename;
    DockRead *myDockRead;

    QActionGroup *tableGroup;
};

#endif // MAINWINDOW_H


