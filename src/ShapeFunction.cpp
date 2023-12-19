//
// Created by grzeg on 18.12.2023.
//

#include "../headers/ShapeFunction.h"

double ShapeFunction::N1(double ksi, double eta) {
    return 0.25 * (1 - ksi) * (1 - eta);
}

double ShapeFunction::N2(double ksi, double eta) {
    return 0.25 * (1 + ksi) * (1 - eta);
}

double ShapeFunction::N3(double ksi, double eta) {
    return 0.25 * (1 + ksi) * (1 + eta);
}

double ShapeFunction::N4(double ksi, double eta) {
    return 0.25 * (1 - ksi) * (1 + eta);
}

double ShapeFunction::dNxdKsi(int x, double eta) {
    if(x == 1)
        return -0.25 * (1 - eta);
    else if(x == 2)
        return 0.25 * (1 - eta);
    else if(x == 3)
        return 0.25 * (1 + eta);
    else if(x == 4)
        return -0.25 * (1 + eta);
    else {
        std::string error_message = "x out of range";
        throw std::invalid_argument(error_message);
    }
}

double ShapeFunction::dNxdEta(int x, double ksi) {
    if (x == 1)
        return -0.25 * (1 - ksi);
    else if (x == 2)
        return -0.25 * (1 + ksi);
    else if (x == 3)
        return 0.25 * (1 + ksi);
    else if (x == 4)
        return 0.25 * (1 - ksi);
    else {
        std::string error_message = "x out of range";
        throw std::invalid_argument(error_message);
    }
}
