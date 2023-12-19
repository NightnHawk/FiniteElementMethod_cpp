//
// Created by grzeg on 18.12.2023.
//

#include "../headers/GaussLegendre.h"

double GaussLegendre::Legendre(int n, double x) {
    if (n == 0) return 1.0;
    if (n == 1) return x;
    return ((2.0 * n - 1.0) * x * Legendre(n - 1, x) - (n - 1) * Legendre(n - 2, x)) / n;
}

double GaussLegendre::dLegendre(int n, double x) {
    return n * (x * Legendre(n, x) - Legendre(n - 1, x)) / (x * x - 1);
}

std::vector<std::pair<double, double>> GaussLegendre::getGaussLegendre(unsigned int n) {
    std::vector<std::pair<double, double>> results(n);

    int size = results.size() - 1;

    for (int i = 0; i < n; i++) {
        double x = cos(M_PI * (i + 0.75) / (n + 0.5));
        while (true) {
            double dx = -Legendre(n, x) / dLegendre(n, x);
            x += dx;
            if (std::abs(dx) < 1e-15) break;
        }

        results[size - i].first = x;
        results[size - i].second = 2.0 / ((1.0 - x * x) * dLegendre(n, x) * dLegendre(n, x));
    }

    return results;
}
