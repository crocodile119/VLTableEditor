/*
 * leadata.h
 *
 *  Created on: 20/gen/2021
 *      Author: GIORCARM
 */

#ifndef LEADATA_H
#define LEADATA_H

struct leadata {
    int formulaNumber;
    double wavelenght1;
    double wavelenght2;
    double time1;
    double time2;
    int C1;
    int C2;
    int C3;
    int C4;
    int C5;
    int C6;
    int C7;
    int t;
    int effects;
    double formula;
    int sort;
};

enum classData{CLASSE_1_1M, CLASSE_2_1M, CLASSE_3R, CLASSE_3B};

#endif /* LEADATA_H */
