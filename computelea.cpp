#include "computelea.h"
#include "leadata.h"
#include "empleatables.h"
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <iostream>
#include <cmath>
#include "tablescontroller.h"

using namespace std;

ComputeLEA::ComputeLEA():leaStructValues_1M{}, leaStructValues_3R{}, leaStructValues_3B{},
    LEA_Formula(nullptr), LEA_FormulaSort(nullptr), LEA_FormulaTipo(nullptr),
    LEA_FormulaUnit(nullptr), myLeaData_1M{}, myLeaData_3R{}, myLeaData_3B{}
{
    /*********************************************************************************
    * Con il singleton sono certo che vi sarà un'unica istanza della classe LeaTable *
    * anche instanziando più oggetti di tipo ComputeLEA                              *
    **********************************************************************************/

    leaStructValues_1M=TablesController::getInstance()->writeLeaInStructValues_1_1M();
    leaStructValues_3R=TablesController::getInstance()->writeLeaInStructValues_3R();
    leaStructValues_3B=TablesController::getInstance()->writeLeaInStructValues_3B();
}

void ComputeLEA::writeLeaInStructValues(classData myClassData)
{
    if(myClassData==CLASSE_1_1M)
        leaStructValues_1M=TablesController::getInstance()->writeLeaInStructValues_1_1M();
    if(myClassData==CLASSE_3R)
        leaStructValues_3R=TablesController::getInstance()->writeLeaInStructValues_3R();
    if(myClassData==CLASSE_3B)
        leaStructValues_3B=TablesController::getInstance()->writeLeaInStructValues_3B();
}

QString ComputeLEA::create_LEA_Table_1M()
{
    int maxIndex;
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
    QString tableName;

    maxIndex=EmpLeaTables::TABLEROW_1_1M;
    tableName="LEA 1 e 1M";
    html=EmpLeaTables::HTML_HEADER;

    html +="<h2>Tabella "+ tableName +"</h2>\n"
           "<table width=\"100%\">\n"
                       "<td>N</td>\n"
                       "<td>&lambda;<sub>1</sub></td>\n"
                       "<td>&lambda;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n"
                       "<td>Formula</td></tr>\n";

    for(int index=0; index<maxIndex; index++)
    {
    wavelength1=QString::number(leaStructValues_1M.at(index).wavelenght1);
    wavelength2=QString::number(leaStructValues_1M.at(index).wavelenght2);
    time1=QString::number(leaStructValues_1M.at(index).time1);
    time2=QString::number(leaStructValues_1M.at(index).time2);

    myFormula=QString::fromStdString(valuateFormula(leaStructValues_1M.at(index)));
    myFormulaTipo=QString::fromStdString(valuateFormulaTipo(leaStructValues_1M.at(index)));
    myFormulaUnit=QString::fromStdString(valuateFormulaUnit(leaStructValues_1M.at(index)));

    myRadiation=typeOfRadiation(leaStructValues_1M.at(index).effects);
    myEyeDamage=typeOfEyeDamage(leaStructValues_1M.at(index).effects);
    mySkinDamage=typeOfSkinDamage(leaStructValues_1M.at(index).effects);

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

QString ComputeLEA::create_LEA_Table_3R()
{
    int maxIndex;
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
    QString tableName;

    maxIndex=EmpLeaTables::TABLEROW_3R;
    tableName="LEA 3R";
    html=EmpLeaTables::HTML_HEADER;

    html +="<h2>Tabella "+ tableName +"</h2>\n"
           "<table width=\"100%\">\n"
                       "<td>N</td>\n"
                       "<td>&lambda;<sub>1</sub></td>\n"
                       "<td>&lambda;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n"
                       "<td>Formula</td></tr>\n";

    for(int index=0; index<maxIndex; index++)
    {
    wavelength1=QString::number(leaStructValues_3R.at(index).wavelenght1);
    wavelength2=QString::number(leaStructValues_3R.at(index).wavelenght2);
    time1=QString::number(leaStructValues_3R.at(index).time1);
    time2=QString::number(leaStructValues_3R.at(index).time2);

    myFormula=QString::fromStdString(valuateFormula(leaStructValues_3R.at(index)));
    myFormulaTipo=QString::fromStdString(valuateFormulaTipo(leaStructValues_3R.at(index)));
    myFormulaUnit=QString::fromStdString(valuateFormulaUnit(leaStructValues_3R.at(index)));

    myRadiation=typeOfRadiation(leaStructValues_3R.at(index).effects);
    myEyeDamage=typeOfEyeDamage(leaStructValues_3R.at(index).effects);
    mySkinDamage=typeOfSkinDamage(leaStructValues_3R.at(index).effects);

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

QString ComputeLEA::create_LEA_Table_3B()
{
    int maxIndex;
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
    QString tableName;

    maxIndex=EmpLeaTables::TABLEROW_3B;
    tableName="LEA 3B";
    html=EmpLeaTables::HTML_HEADER;

    html +="<h2>Tabella "+ tableName +"</h2>\n"
           "<table width=\"100%\">\n"
                       "<td>N</td>\n"
                       "<td>&lambda;<sub>1</sub></td>\n"
                       "<td>&lambda;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n"
                       "<td>Formula</td></tr>\n";

    for(int index=0; index<maxIndex; index++)
    {
    wavelength1=QString::number(leaStructValues_3B.at(index).wavelenght1);
    wavelength2=QString::number(leaStructValues_3B.at(index).wavelenght2);
    time1=QString::number(leaStructValues_3B.at(index).time1);
    time2=QString::number(leaStructValues_3B.at(index).time2);

    myFormula=QString::fromStdString(valuateFormula(leaStructValues_3B.at(index)));
    myFormulaTipo=QString::fromStdString(valuateFormulaTipo(leaStructValues_3B.at(index)));
    myFormulaUnit=QString::fromStdString(valuateFormulaUnit(leaStructValues_3B.at(index)));

    myRadiation=typeOfRadiation(leaStructValues_3B.at(index).effects);
    myEyeDamage=typeOfEyeDamage(leaStructValues_3B.at(index).effects);
    mySkinDamage=typeOfSkinDamage(leaStructValues_3B.at(index).effects);

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

string ComputeLEA::valuateFormula(leadata &myLeaData)
{
    string tabC1;
    string tabC2;
    string tabC3;
    string tabC4;
    string tabC5;
    string tabC6;
    string tabC7;
    string tabt;
    string Tipo;
    string coeffValue;

  if (myLeaData.C1==0)
     tabC1 = "";
  else
      tabC1 = " C<sub>1</sub>";

  if (myLeaData.C2==0)
     tabC2="";
  else
      tabC2=" C<sub>2</sub>";

  if (myLeaData.C3==0)
     tabC3="";
  else
      tabC3=" C<sub>3</sub>";

  if (myLeaData.C4==0)
     tabC4="";
  else
      tabC4=" C<sub>4</sub>";
  
  if (myLeaData.C5==0)
     tabC5="";
  else
      tabC5=" C<sub>5</sub>";
  
  if (myLeaData.C6==0)
     tabC6="";
  else
      tabC6=" C<sub>6</sub>";
  
  if (myLeaData.C7==0)
     tabC7="";
  else
      tabC7=" C<sub>7</sub>";

  if (myLeaData.t==0)
    tabt="";
  else if (myLeaData.t==1)
    tabt=" t<sup>0,75</sup>";
  else if (myLeaData.t==2)
    tabt=" t<sup>0,25</sup>";
  else
    tabt=" t";
 
 // Double to string conversion, the C++03 way:
	ostringstream sstream;
    sstream << myLeaData.formula;
	coeffValue = sstream.str();

    string Formula = coeffValue + tabt + tabC1 + tabC2 + tabC3 + tabC4 + tabC5+ tabC6+ tabC7;

    return Formula;
}

string ComputeLEA::valuateFormulaTipo(leadata &myLeaData)
{
    string Tipo;

    if (myLeaData.sort==1)
         Tipo="E";
    else if (myLeaData.sort==2)
         Tipo="H";
    else if (myLeaData.sort==3)
         Tipo="P";
    else
         Tipo="Q";

    return Tipo;
}


string ComputeLEA::valuateFormulaUnit(leadata &myLeaData)
{
    string FormulaUnit;

    if (myLeaData.sort==1)
        FormulaUnit="W/m<sup>2</sup>";
    else if (myLeaData.sort==2)
        FormulaUnit="J/m<sup>2</sup>";
    else if (myLeaData.sort==3)
        FormulaUnit="W";
    else
       FormulaUnit="J";

    return FormulaUnit;
}

string ComputeLEA::getRadiation() const
{
    return radiation;
}

string ComputeLEA::getSkinDamage() const
{
    return skinDamage;
}

string ComputeLEA::getEyeDamage() const
{
    return eyeDamage;
}

QString ComputeLEA::typeOfSkinDamage(const int &_effects)
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

QString ComputeLEA::typeOfEyeDamage(const int &_effects)
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

QString ComputeLEA::typeOfRadiation(const int & _effects)
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
