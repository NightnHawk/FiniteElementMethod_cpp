//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_GAUSSLEGENDRE_H
#define FEM_GAUSSLEGENDRE_H


#include <cmath>
#include <vector>
#include <utility>

class GaussLegendre {
public:
    static double Legendre(int n, double x);

    static double dLegendre(int n, double x);

    static std::vector<std::pair<double, double>> getGaussLegendre(unsigned int n);
};


#endif //FEM_GAUSSLEGENDRE_H
