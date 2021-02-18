#include "computeemp.h"
#include "empdata.h"
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include "tablescontroller.h"

using namespace std;
	
ComputeEMP::ComputeEMP(): empStructValues{}, EMP_Result(0), EMP_FormulaSort(0), myEmpData{},
    CA(0),CB(0), CC(0), CE(0), T1(0), T2(0), photoGamma(0)
{
    /*********************************************************************************
    * Con il singleton sono certo che vi sarà un'unica istanza della classe LeaTable *
    * anche instanziando più oggetti di tipo ComputeLEA                              *
    **********************************************************************************/

    empStructValues=TablesController::getInstance()->writeEmpInStructValues();
}

void ComputeEMP::writeEmpInStructValues()
{
    empStructValues=TablesController::getInstance()->writeEmpInStructValues();
}

QString ComputeEMP::create_EMP_Table()
{
    int maxIndex=EmpLeaTables::TABLEROW_EMP;
    QString myFormula;
    QString myFormulaTipo;
    QString myFormulaUnit;
    QString wavelength1;
    QString wavelength2;
    QString time1;
    QString time2;
    QString html;
    QString formulaNumber;
    QString myRadiation;
    QString myEyeDamage;
    QString mySkinDamage;

    html +=EmpLeaTables::HTML_HEADER+"<h2>Tabella EMP occhi</h2>\n"
           "<table width=\"100%\">\n"
                       "<td>N</td>\n"
                       "<td>&lambda;<sub>1</sub></td>\n"
                       "<td>&lambda;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n"
                       "<td>Formula</td></tr>\n";

    for(int index=0; index<maxIndex; index++)
    {
    wavelength1=QString::number(empStructValues.at(index).wavelenght1);
    wavelength2=QString::number(empStructValues.at(index).wavelenght2);
    time1=QString::number(empStructValues.at(index).time1);
    time2=QString::number(empStructValues.at(index).time2);

    myFormula=QString::fromStdString(valuateFormula(empStructValues.at(index)));
    myFormulaTipo=QString::fromStdString(valuateFormulaTipo(empStructValues.at(index)));
    myFormulaUnit=QString::fromStdString(valuateFormulaUnit(empStructValues.at(index)));

    myRadiation=typeOfRadiation(empStructValues.at(index).effects);
    myEyeDamage=typeOfEyeDamage(empStructValues.at(index).effects);
    mySkinDamage=typeOfSkinDamage(empStructValues.at(index).effects);

    html +=
    "<tr><td>"+ formulaNumber +"</td>\n"
    "<td>"+ wavelength1 +"</td>\n"
    "<td>"+ wavelength2 +"</td>\n"
    "<td>"+ time1 +"</td>\n"
    "<td>"+ time2 +"</td>\n"
    "<td>"+ myFormulaTipo+ " = "+ myFormula + " " + myFormulaUnit+"</td></tr>\n";
    }

    html+= "</table><br>\n";

    return html;
}

string ComputeEMP::getRadiation() const
{
    return radiation;
}

string ComputeEMP::getSkinDamage() const
{
    return skinDamage;
}

string ComputeEMP::getEyeDamage() const
{
    return eyeDamage;
}

string ComputeEMP::valuateFormula(const empdata & myEmpData)
{
    string tabCA;
    string tabCB;
    string tabCC;
    string tabCE;
    string tabt;
    string Tipo;
    string coeffValue;

    if (myEmpData.sort==0)
         Tipo="E";
    else if (myEmpData.sort==1)
          Tipo="H";

    if (myEmpData.CA==0)
     tabCA = "";
    else
      tabCA = " C<sub>A</sub>";

    if (myEmpData.CB==0)
     tabCB="";
    else
      tabCB=" C<sub>B</sub>";

    if (myEmpData.CC==0)
     tabCC="";
    else
      tabCC=" C<sub>C</sub>";

    if (myEmpData.CE==0)
     tabCE="";
    else
      tabCE=" C<sub>E</sub>";

    if (myEmpData.t==1)
      tabt=" t<sup>0,75</sup>";
    else if (myEmpData.t==2)
      tabt=" t<sup>0,25</sup>";
    else
     tabt="";
 
 // Double to string conversion, the C++03 way:
	ostringstream sstream;
    sstream << myEmpData.formula;
	coeffValue = sstream.str();

    EMP_Formula = coeffValue + tabt + tabCA + tabCB + tabCC + tabCE;

    return EMP_Formula;
}

string ComputeEMP::valuateFormulaTipo(const empdata & myEmpData)
{
    string Tipo;

    if (myEmpData.sort==0)
         Tipo="E";
    else
         Tipo="H";

    return Tipo;
}

string ComputeEMP::valuateFormulaUnit(const empdata & myEmpData)
{
    string FormulaUnit;

    if (myEmpData.sort==0)
         FormulaUnit="W/m<sup>2</sup>";
    else
         FormulaUnit="J/m<sup>2</sup>";

    return FormulaUnit;
}

QString ComputeEMP::typeOfSkinDamage(const int &_effects)
{
    QString mySkinDamage;
    switch ((EmpLeaTables::typeOfOutput)_effects)
        {
        case EmpLeaTables::UV:
        mySkinDamage="eritema;";
        break;

        case EmpLeaTables::VIS:
        mySkinDamage="danno termico";
        break;

        case EmpLeaTables::IRA:
        mySkinDamage="danno termico";
        break;

        case EmpLeaTables::IRA_2:
        mySkinDamage="danno termico";
        break;

        case EmpLeaTables::VIS_2:
        mySkinDamage="danno termico";
        break;

        case EmpLeaTables::VIS_3:
        mySkinDamage="danno termico";
        break;

        case EmpLeaTables::IRA_IRB:
        mySkinDamage="danno termico";
        break;

        default:
        mySkinDamage="c'è qualcosa che non va";
        break;
        }
    return mySkinDamage;
}

QString ComputeEMP::typeOfEyeDamage(const int &_effects)
{
    QString myEyeDamage;
        switch ((EmpLeaTables::typeOfOutput)_effects)
        {
        case EmpLeaTables::UV:
        myEyeDamage="danno fotochimico e danno termico;";
        break;

        case EmpLeaTables::VIS:
        myEyeDamage="retina";
        break;

        case EmpLeaTables::IRA:
        myEyeDamage="retina";
        break;

        case EmpLeaTables::IRA_2:
        myEyeDamage="danno termico";
        break;

        case EmpLeaTables::VIS_2:
        myEyeDamage="retina, danno forochimico e danno termico";
        break;

        case EmpLeaTables::VIS_3:
        myEyeDamage="retina";
        break;

        case EmpLeaTables::IRA_IRB:
        myEyeDamage="danno termico";
        break;

        default:
        myEyeDamage="c'è qualcosa che non va";
        break;
        }
    return myEyeDamage;
}

QString ComputeEMP::typeOfRadiation(const int & _effects)
{
    QString myRadiation;
        switch ((EmpLeaTables::typeOfOutput)_effects)
        {
        case EmpLeaTables::UV:
        myRadiation="UV";
        break;

        case EmpLeaTables::VIS:
        myRadiation="Visibile";
        break;

        case EmpLeaTables::IRA:
        myRadiation="IRA";
        break;

        case EmpLeaTables::IRA_2:
        myRadiation="IRB";
        break;

        case EmpLeaTables::VIS_2:
        myRadiation="visibile";
        break;

        case EmpLeaTables::VIS_3:
        myRadiation="visibile";
        break;

        case EmpLeaTables::IRA_IRB:
        myRadiation="IRB, IRC";
        break;

        default:
        myRadiation="c'è qualcosa che non va";
        break;
        }
    return myRadiation;
}
