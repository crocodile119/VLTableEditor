#ifndef EMPLEATABLES_H
#define EMPLEATABLES_H

#include "leadata.h"
#include "empdata.h"
#include <QtGui>

class EmpLeaTables
{
public:
    EmpLeaTables();
    ~EmpLeaTables();
    empdata* writeEmpValues();
    leadata* writeLeaValues(classData);
    empdata* getEmpData();
    leadata* getLeaData_1_1M();
    leadata* getLeaData_3R();
    leadata* getLeaData_3B();

private:
    empdata* empValues;
    leadata *leaValues_1_1M;
    leadata *leaValues_3R;
    leadata *leaValues_3B;
};

#endif // EMPLEATABLES_H
