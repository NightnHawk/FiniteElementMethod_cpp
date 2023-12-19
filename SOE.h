//
// Created by grzeg on 19.12.2023.
//

#ifndef FEM_SOE_H
#define FEM_SOE_H


#include "headers/Matrix.h"
#include "headers/Grid.h"

class SOE {
private:
    unsigned int n;
    Matrix<double> soe;
    std::vector<double> sol;
//    Matrix<double> solutions;

public:
    SOE(unsigned int n) : n(n), soe(n, (n + 1, 0.0)), sol(n, 0.0) {};

    std::vector<double> solve(Grid &grid) {
        for(const auto &element: grid.getElements()) {
            auto H_ = element.getHMatrix() + element.getHbcMatrix() + element.getCMatrix() * (1.0 / grid.getGlobalData().getValue(
                    static_cast<int>(Simulation::SimulationStepTime)));

            for(int i = 0; i < 4; i++) {
                std::vector<double> element_temp;
                for(int j = 0; j < element.getNodes().size(); j++) {
                    element_temp.push_back(element.getNodes()[j].getTemp());
                }

                sol[element.getIDs()[i] - 1] += element.getPVector()[i] + (element.getCMatrix() * (1.0 / grid.getGlobalData().getValue(
                        static_cast<int>(Simulation::SimulationStepTime))) * element_temp)[i];

                for(int j = 0; j < 4; j++) {
                    soe(element.getIDs()[i] - 1, element.getIDs()[j] - 1) += H_(i, j);
                }
            }
        }

        for(int i = 0; i < soe.numRows(); i++) {
            int lastIndex = soe.getRow(i).size() - 1;
            soe(i, lastIndex) += sol[i];
        }

        return Matrix<double>::solveEquations(soe);
    }
};


#endif //FEM_SOE_H
