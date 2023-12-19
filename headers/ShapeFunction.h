//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_SHAPEFUNCTION_H
#define FEM_SHAPEFUNCTION_H


#include <string>
#include <stdexcept>

class ShapeFunction {
public:

    static double N1(double ksi, double eta);

    static double N2(double ksi, double eta);

    static double N3(double ksi, double eta);

    static double N4(double ksi, double eta);

    static double dNxdKsi(int x, double eta);

    static double dNxdEta(int x, double ksi);
};


static double (*N[])(double ksi, double eta) = {ShapeFunction::N1, ShapeFunction::N2, ShapeFunction::N3, ShapeFunction::N4};

#endif //FEM_SHAPEFUNCTION_H
