#include "computelea.h"
#include "leadata.h"
#include "empleatables.h"
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

ComputeLEA::ComputeLEA()
{
    leaStructValues_1M=new leadata[41];
    leaStructValues_3R=new leadata[38];
    leaStructValues_3B=new leadata[21];

    /*********************************************************************************
    * Con il singleton sono certo che vi sarà un'unica istanza della classe LeaTable *
    * anche instanziando più oggetti di tipo ComputeLEA                              *
    **********************************************************************************/

    leaStructValues_1M=TablesController::getInstance()->writeLeaInStructValues(CLASSE_1_1M);
    leaStructValues_3R=TablesController::getInstance()->writeLeaInStructValues(CLASSE_3R);
    leaStructValues_3B=TablesController::getInstance()->writeLeaInStructValues(CLASSE_3B);
}

void ComputeLEA::writeLeaInStructValues(classData myClassData)
{
    if(myClassData==CLASSE_1_1M)
        leaStructValues_1M=TablesController::getInstance()->writeLeaInStructValues(myClassData);
    if(myClassData==CLASSE_3R)
        leaStructValues_3R=TablesController::getInstance()->writeLeaInStructValues(myClassData);
    if(myClassData==CLASSE_3B)
        leaStructValues_3B=TablesController::getInstance()->writeLeaInStructValues(myClassData);
}

QString ComputeLEA::create_LEA_Table(classData myClassData)
{
    int maxIndex;
    leadata myLeaData;
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
    leadata* myLeaDataArray;
    QString tableName;

    if(myClassData==CLASSE_1_1M)
    {
        maxIndex=41;
        myLeaDataArray=leaStructValues_1M;
        tableName="LEA 1 e 1M";
    }
    else if(myClassData==CLASSE_3R)
    {
        maxIndex=38;
        myLeaDataArray=leaStructValues_3R;
        tableName="LEA 3R";
    }
    else
    {
        maxIndex=21;
        myLeaDataArray=leaStructValues_3B;
        tableName="LEA 3B";
    }

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
    myLeaData=myLeaDataArray[index];

    int myRow=index+1;
    QString row=QString::number(myRow);
    wavelength1=QString::number(myLeaData.wavelenght1);
    wavelength2=QString::number(myLeaData.wavelenght2);
    time1=QString::number(myLeaData.time1);
    time2=QString::number(myLeaData.time2);

    myFormula=QString::fromStdString(valuateFormula(myLeaData));
    myFormulaTipo=QString::fromStdString(valuateFormulaTipo(myLeaData));
    myFormulaUnit=QString::fromStdString(valuateFormulaUnit(myLeaData));

    myRadiation=typeOfRadiation(myLeaData.effects);
    myEyeDamage=typeOfEyeDamage(myLeaData.effects);
    mySkinDamage=typeOfSkinDamage(myLeaData.effects);

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

QString ComputeLEA::typeOfEyeDamage(const int &_effects)
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

QString ComputeLEA::typeOfRadiation(const int & _effects)
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

ComputeLEA::~ComputeLEA()
{
    delete leaStructValues_1M;
    delete leaStructValues_3R;
    delete leaStructValues_3B;
}
