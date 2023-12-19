//
// Created by grzeg on 18.12.2023.
//

#include "../headers/Surface.h"

Surface::Surface(unsigned int n) {
    surface_tab = std::vector<Matrix<double>>(4, Matrix<double>(n, 4, 0.0));
    auto surfaces = std::vector(4, std::vector<std::vector<double>>(n, std::vector<double>(4, 0.0)));
    auto gaussLegendre = GaussLegendre::getGaussLegendre(n);
    std::vector<double> points;
    std::vector<double> weights;
    for(auto root: gaussLegendre) {
        points.push_back(root.first);
        weights.push_back(root.second);
    }

    for(int surface = 0; surface < 4; surface++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < 4; j++) {
                std::pair<double, double> cord;
                if(surface == 0) cord = std::pair<double, double>(points.at(i), -1.0);
                if(surface == 1) cord = std::pair<double, double>(1.0, points.at(i));
                if(surface == 2) cord = std::pair<double, double>(points.at(i), 1.0);
                if(surface == 3) cord = std::pair<double, double>(-1.0, points.at(i));
                if(j == surface or j == (surface + 1)%4) {
                    surfaces[surface][i][j] = N[j](cord.first, cord.second);
                }
                else {
                    surfaces[surface][i][j] = 0.0;
                }
            }
        }
    }

    std::reverse(surfaces[2].begin(), surfaces[2].end());

    for(auto &row: surfaces[3]) {
        std::reverse(row.begin(), row.end());
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 4; k++) {
                surface_tab[i](j, k) = surfaces[i][j][k];
            }
        }
    }
}
