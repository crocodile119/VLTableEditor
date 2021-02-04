#ifndef COMPUTELEA_H
#define COMPUTELEA_H
#include "leadata.h"
#include "empleatables.h"
#include <string>
#include <QtGui>

using namespace std;

class ComputeLEA
{
public:
    ComputeLEA();
    ~ComputeLEA();
	string getRadiation() const;
	string getSkinDamage() const;
    string getEyeDamage() const;
    double getGamma() const;
    string valuateFormula(leadata &);
    void writeLeaInStructValues(classData);

    string valuateFormulaTipo(leadata &);
    string valuateFormulaUnit(leadata &);

    QString create_LEA_Table(classData);
    QString typeOfEyeDamage(const int&);
    QString typeOfRadiation(const int&);
    QString typeOfSkinDamage(const int&);

private:
    int n_lea=4;
    leadata* leaStructValues_1M;
    leadata* leaStructValues_3R;
    leadata* leaStructValues_3B;

    EmpLeaTables* myEmpleaTables;

    string *LEA_Formula;
    int *LEA_FormulaSort;
    string *LEA_FormulaTipo;
    string *LEA_FormulaUnit;

    leadata myLeaData_1M;
    leadata myLeaData_3R;
    leadata myLeaData_3B;

    string radiation;
    string skinDamage;
    string eyeDamage;
};
#endif // COMPUTELEA_H
