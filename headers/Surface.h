//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_SURFACE_H
#define FEM_SURFACE_H


#include <vector>
#include <algorithm>
#include "Matrix.h"
#include "ShapeFunction.h"
#include "GaussLegendre.h"

class Surface {
public:
    std::vector<Matrix<double>> surface_tab;

    Surface(unsigned int n);
};


#endif //FEM_SURFACE_H
