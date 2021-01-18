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
    void writeBinaryData();
    void readAsciiData();
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

private:
    Ui::MainWindow *ui;
    double wavelength;
    double time;
    enum binaryData{EMP, CLASSE_1_1M, CLASSE_3R};
    binaryData myBinaryData;
    int maxRow;
    int maxColumn;
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


