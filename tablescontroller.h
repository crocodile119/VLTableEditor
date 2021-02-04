#ifndef TABLESCONTROLLER_H
#define TABLESCONTROLLER_H
#include "empleatables.h"


class TablesController
{
public:
    TablesController();
    // Funzione membro del singleton
    static TablesController *getInstance();

    //Distrugge l'istanza del singleton
    static void destroy();
    leadata* writeLeaInStructValues(classData);
    empdata* writeEmpInStructValues();

private:

  static TablesController *singleton; // pointer to the singleton

   EmpLeaTables *myEmpLeaTables;

};

#endif // TABLESCONTROLLER_H
