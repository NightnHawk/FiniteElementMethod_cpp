//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_UNIVERSALELEMENT_H
#define FEM_UNIVERSALELEMENT_H


#include "Matrix.h"
#include "GaussLegendre.h"
#include "ShapeFunction.h"


class UniversalElement {
public:
    unsigned int n;
    Matrix<double> dNdKsi;
    Matrix<double> dNdEta;
    Matrix<double> N_matrix;

    UniversalElement(int n);

    void print_dNdKsi();
    void print_dNdEta();
    void print_N_matrix();
};


#endif //FEM_UNIVERSALELEMENT_H
