//
// Created by grzeg on 18.12.2023.
//

#include "../headers/UniversalElement.h"

UniversalElement::UniversalElement(int n) : n(n), dNdKsi(Matrix<double>(n*n, 4, 0.0)), dNdEta(Matrix<double>(n*n, 4, 0.0)),
                                            N_matrix(Matrix<double>(n*n, 4, 0.0)) {
    auto gaussLegendre = GaussLegendre::getGaussLegendre(n);
    std::vector<double> points;
    std::vector<double> weights;
    for(auto root: gaussLegendre) {
        points.push_back(root.first);
        weights.push_back(root.second);
    }

    double first, second;

    for(int i = 0; i < n * n; i++) {
        first = i % n;
        second = i / n;
        for(int j = 0; j < 4; j++) {
            dNdKsi(i, j) = ShapeFunction::dNxdKsi(j + 1, points.at(i / n));
            dNdEta(i, j) = ShapeFunction::dNxdEta(j + 1, points.at(i % n));
            N_matrix(i, j) = N[j](points.at(first), points.at(second));
        }
    }
}

void UniversalElement::print_dNdKsi() {
    std::cout << "dNdKsi (" << std::to_string(n) << "):" << std::endl;
    dNdKsi.print();
}

void UniversalElement::print_dNdEta() {
    std::cout << "dNdEta (" << std::to_string(n) << "):" << std::endl;
    dNdEta.print();
}

void UniversalElement::print_N_matrix() {
    std::cout << "N matrix (" << std::to_string(n) << "):" << std::endl;
    N_matrix.print();
}
