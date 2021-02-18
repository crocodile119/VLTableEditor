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
	string getRadiation() const;
	string getSkinDamage() const;
    string getEyeDamage() const;
    double getGamma() const;
    string valuateFormula(leadata &);
    void writeLeaInStructValues(classData);

    string valuateFormulaTipo(leadata &);
    string valuateFormulaUnit(leadata &);

    QString create_LEA_Table_1M();
    QString create_LEA_Table_3R();
    QString create_LEA_Table_3B();

    QString typeOfEyeDamage(const int&);
    QString typeOfRadiation(const int&);
    QString typeOfSkinDamage(const int&);

private:
    int n_lea=4;
    std::array<leadata, EmpLeaTables::TABLEROW_1_1M> leaStructValues_1M;
    std::array<leadata, EmpLeaTables::TABLEROW_3R>leaStructValues_3R;
    std::array<leadata, EmpLeaTables::TABLEROW_3B>leaStructValues_3B;

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
