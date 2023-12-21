//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_GLOBALDATA_H
#define FEM_GLOBALDATA_H


#include <vector>
#include <string>
#include <map>

enum class Simulation {
    SimulationTime = 0,
    SimulationStepTime = 1,
    Conductivity = 2,
    Alfa = 3,
    Tot = 4,
    InitialTemp = 5,
    Density = 6,
    SpecificHeat = 7,
    Nodes = 8,
    Elements = 9
};

class GlobalData {
private:
    std::vector<double> values;
    std::map<std::string, int> dictionary = {
            {"SimulationTime", 0},
            {"SimulationStepTime", 1},
            {"Conductivity", 2},
            {"Alfa", 3},
            {"Tot", 4},
            {"InitialTemp", 5},
            {"Density", 6},
            {"SpecificHeat", 7},
            {"Nodes", 8},
            {"Elements", 9}};
public:
    GlobalData() : values(10, 0.0) {}

    std::map<std::string, int> &getDictionary();

    const std::vector<double> &getValues() const;

    const double &getValue(int index) const;

    void setValues(const std::vector<double> &values);

    void setValue(int index, double value);
};


#endif //FEM_GLOBALDATA_H
