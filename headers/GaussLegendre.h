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
// Funkcja oblicza wielomian Legendre-a n-tego stopnia
    static double Legendre(int n, double x);

// Funkcja oblicza pochodną wielomianu Legendre-a n-tego stopnia
    static double dLegendre(int n, double x);

// Funkcja oblicza i zwraca wektor par punkt-waga dla pierwiastków (punktów kwadratury) w metodzie Gaussa-Legendre-a
    static std::vector<std::pair<double, double>> getGaussLegendre(unsigned int n);
};


#endif //FEM_GAUSSLEGENDRE_H
