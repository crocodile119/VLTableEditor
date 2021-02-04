#include "empleatables.h"
#include "leadata.h"
#include "empdata.h"
#include <QTextStream>
#include <QDataStream>
#include <QFile>

EmpLeaTables::EmpLeaTables()
{
    Q_INIT_RESOURCE(writeVLE_Tables);

    leaValues_1_1M=writeLeaValues(CLASSE_1_1M);
    leaValues_3R=writeLeaValues(CLASSE_3R);
    leaValues_3B=writeLeaValues(CLASSE_3B);
    empValues=writeEmpValues();
}

leadata* EmpLeaTables::writeLeaValues(classData myClassData) {

    int _formulaNumber;
    double _wavelenght1;
    double _wavelenght2;
    double _time1;
    double _time2;
    int _effects;
    int _t;
    int _C1;
    int _C2;
    int _C3;
    int _C4;
    int _C5;
    int _C6;
    int _C7;
    double _formula;
    int _sort;
    int maxRow;
    QString filename;

    if(myClassData==CLASSE_1_1M)
    {
        maxRow=41;
        filename=":/CLASSE_1_1M_dataBinary.dat";
    }
    else if(myClassData==CLASSE_3R)
    {
        maxRow=38;
        filename=":/CLASSE_3R_dataBinary.dat";
    }
    else
    {
        maxRow=21;
        filename=":/CLASSE_3B_dataBinary.dat";
    }

    leadata* LeaValues= new leadata[maxRow];

    QFile fileBinary(filename);
    if (!fileBinary.open(QIODevice::ReadOnly))
    {
        qDebug("Can't open file");
        exit(1);
    }

    QDataStream in(&fileBinary);
    in.setVersion(QDataStream::Qt_4_3);

    for(int row=0; row<maxRow; row++)
    {

              in >> _formulaNumber >> _wavelenght1 >> _wavelenght2 >> _time1 >> _time2 >> _C1 >> _C2
                    >> _C3 >> _C4 >> _C5 >> _C6 >> _C7 >> _t >> _effects >> _formula >> _sort;


             LeaValues[row].formulaNumber=_formulaNumber;
             LeaValues[row].wavelenght1=_wavelenght1;
             LeaValues[row].wavelenght2=_wavelenght2;
             LeaValues[row].time1=_time1;
             LeaValues[row].time2=_time2;
             LeaValues[row].t=_t;
             LeaValues[row].effects=_effects;
             LeaValues[row].C1=_C1;
             LeaValues[row].C2=_C2;
             LeaValues[row].C3=_C3;
             LeaValues[row].C4=_C4;
             LeaValues[row].C5=_C5;
             LeaValues[row].C6=_C6;
             LeaValues[row].C7=_C7;
             LeaValues[row].formula=_formula;
             LeaValues[row].sort=_sort;
    }
     fileBinary.close();

     return LeaValues;
}

empdata* EmpLeaTables::writeEmpValues() {

    int _formulaNumber;
    double _wavelenght1;
    double _wavelenght2;
    double _time1;
    double _time2;
    int _effects;
    int _t;
    int _CA;
    int _CB;
    int _CC;
    int _CE;
    double _formula;
    int _sort;
    int rowNumber=70;
    QString filename=":/EMPdataBinary.dat";

    empdata* empValues= new empdata[rowNumber];

    QFile fileBinary(filename);
    if (!fileBinary.open(QIODevice::ReadOnly))
    {
        qDebug("Can't open file");
        exit(1);
    }

    QDataStream in(&fileBinary);
    in.setVersion(QDataStream::Qt_4_3);

    for(int row=0; row<rowNumber; row++)
    {

              in >> _formulaNumber >> _wavelenght1 >> _wavelenght2 >> _time1 >> _time2 >> _CA >> _CB
                    >> _CC >> _CE >> _t >> _effects >> _formula >> _sort;


             empValues[row].formulaNumber=_formulaNumber;
             empValues[row].wavelenght1=_wavelenght1;
             empValues[row].wavelenght2=_wavelenght2;
             empValues[row].time1=_time1;
             empValues[row].time2=_time2;
             empValues[row].t=_t;
             empValues[row].effects=_effects;
             empValues[row].CA=_CA;
             empValues[row].CB=_CB;
             empValues[row].CC=_CC;
             empValues[row].CE=_CE;
             empValues[row].formula=_formula;
             empValues[row].sort=_sort;
    }
     fileBinary.close();

     return empValues;
}

leadata* EmpLeaTables::getLeaData_1_1M()
{
   return leaValues_1_1M;
}

leadata* EmpLeaTables::getLeaData_3R()
{
   return leaValues_3R;
}

leadata* EmpLeaTables::getLeaData_3B()
{
   return leaValues_3B;
}

EmpLeaTables::~EmpLeaTables()
{
    delete empValues;
    delete leaValues_1_1M;
    delete leaValues_3R;
    delete leaValues_3B;
}
