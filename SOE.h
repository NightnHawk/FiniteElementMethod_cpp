//
// Created by grzeg on 19.12.2023.
//

#ifndef FEM_SOE_H
#define FEM_SOE_H


#include <fstream>
#include <filesystem>
#include "headers/Matrix.h"
#include "headers/Grid.h"

class SOE {
private:
    unsigned int n;
    Matrix<double> soe;
    std::vector<std::vector<double>> solutions;

public:
    SOE(unsigned int n) : n(n), soe(n, (n + 1), 0.0) {};

    std::vector<double> solve(Grid &grid);

    void generate_vtk(Grid &grid, std::string nameSchema);
};


#endif //FEM_SOE_H
