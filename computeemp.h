#ifndef COMPUTEEMP_H
#define COMPUTEEMP_H
#include "empdata.h"
#include "empleatables.h"
#include <string>
#include <QtGui>

using namespace std;



class ComputeEMP
{
public:
    ComputeEMP();
    ~ComputeEMP();
	string getRadiation() const;
	string getSkinDamage() const;
    string getEyeDamage() const;
	double getGamma() const;
    string valuateFormula(const empdata & myEmpData);

    string valuateFormulaTipo(const empdata & myEmpData);
    string valuateFormulaUnit(const empdata & myEmpData);
    QString create_EMP_Table();

    QString typeOfSkinDamage(const int &);
    QString typeOfEyeDamage(const int &);
    QString typeOfRadiation(const int &);
    void writeEmpInStructValues();

private:
    empdata* empStructValues;

    EmpLeaTables* leaTables;

    double EMP_Result;
    string EMP_Formula;
    int EMP_FormulaSort;
    string EMP_FormulaTipo;
    string EMP_FormulaUnit;

    empdata myEmpData;

    double CA;
    double CB;
    double CC;
    double CE;
    double T1;
    double T2;
    double photoGamma;
    string radiation;
    string skinDamage;
    string eyeDamage;
    string note;
	
};
#endif // COMPUTEEMP_H
