#include "computeemp.h"
#include "empdata.h"
#include <ctype.h>
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

	
ComputeEMP::ComputeEMP()
{
    /*********************************************************************************
    * Con il singleton sono certo che vi sarà un'unica istanza della classe LeaTable *
    * anche instanziando più oggetti di tipo ComputeLEA                              *
    **********************************************************************************/

    empStructValues=new empdata[70];
    empStructValues=TablesController::getInstance()->writeEmpInStructValues();
}

void ComputeEMP::writeEmpInStructValues()
{
    empStructValues=TablesController::getInstance()->writeEmpInStructValues();
}

QString ComputeEMP::create_EMP_Table()
{
    int maxIndex=70;
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


    html="<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n"
        "<html>\n"
        "<head>\n"
        "<meta content=\"text/html; charset=ISO-8859-1\"\n"
        "http-equiv=\"content-type\">\n"
        "<title>Laser Report</title>\n"
            "<style>"
                 "h1, h2, h3, h4 {\n"
                 "font-family: \"Trebuchet MS\", Arial, Helvetica, sans-serif;\n"
                 "}\n"
                 "table, th, td {\n"
                 "font-family: \"Trebuchet MS\", Arial, Helvetica, sans-serif;\n"
                 "font-size: large;\n"
                 "border-width: 1px;\n"
                 "border-color: #dddddd;\n"
                 "border-collapse: collapse;\n"
                 "text-align: left;\n"
                 "}\n"
                 "th {\n"
                 "padding-top: 12px;\n"
                 "padding-bottom: 12px;\n"
                 "text-align: left;\n"
                 "background-color: #00c800;\n"
                 "color: #fafafa;\n"
                 "}\n"
                 "td, th {\n"
                 "padding: 8px;\n"
                 "}\n"
            "</style>\n"
         "</head>\n"
         "<body>\n"
         "<br>\n";

    html +="<h2>Tabella EMP occhi</h2>\n"
           "<table width=\"100%\">\n"
                       "<td>N</td>\n"
                       "<td>&lambda;<sub>1</sub></td>\n"
                       "<td>&lambda;<sub>2</sub></td>\n"
                       "<td>t<sub>1</sub></td>\n"
                       "<td>t<sub>2</sub></td>\n"
                       "<td>Formula</td></tr>\n";

    for(int index=0; index<maxIndex; index++)
    {

    int myRow=index+1;
    QString row=QString::number(myRow);
    wavelength1=QString::number(empStructValues[index].wavelenght1);
    wavelength2=QString::number(empStructValues[index].wavelenght2);
    time1=QString::number(empStructValues[index].time1);
    time2=QString::number(empStructValues[index].time2);

    myFormula=QString::fromStdString(valuateFormula(empStructValues[index]));
    myFormulaTipo=QString::fromStdString(valuateFormulaTipo(empStructValues[index]));
    myFormulaUnit=QString::fromStdString(valuateFormulaUnit(empStructValues[index]));

    myRadiation=typeOfRadiation(empStructValues[index].effects);
    myEyeDamage=typeOfEyeDamage(empStructValues[index].effects);
    mySkinDamage=typeOfSkinDamage(empStructValues[index].effects);

    html +=
    "<tr><td>"+ row +"</td>\n"
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
    switch (_effects)
        {
        case 1:
        mySkinDamage="eritema;";
        break;

        case 2:
        mySkinDamage="danno termico";

        break;

        case 3:
        mySkinDamage="danno termico";
        break;

        case 4:
        mySkinDamage="danno termico";
        break;

        case 5:
        mySkinDamage="danno termico";
        break;

        case 6:
        mySkinDamage="danno termico";
        break;

        case 7:
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
        switch (_effects)
        {
        case 1:
        myEyeDamage="danno fotochimico e danno termico;";
        break;

        case 2:
        myEyeDamage="retina";
        break;

        case 3:
        myEyeDamage="retina";
        break;

        case 4:
        myEyeDamage="danno termico";
        break;

        case 5:
        myEyeDamage="retina, danno forochimico e danno termico";
        break;

        case 6:
        myEyeDamage="retina";
        break;

        case 7:
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
        switch (_effects)
        {
        case 1:
        myRadiation="UV";
        break;

        case 2:
        myRadiation="Visibile";
        break;

        case 3:
        myRadiation="IRA";
        break;

        case 4:
        myRadiation="IRB";
        break;

        case 5:
        myRadiation="visibile";
        break;

        case 6:
        myRadiation="visibile";
        break;

        case 7:
        myRadiation="IRB, IRC";
        break;

        default:
        myRadiation="c'è qualcosa che non va";
        break;
        }
    return myRadiation;
}

ComputeEMP::~ComputeEMP()
{
    delete empStructValues;
}
