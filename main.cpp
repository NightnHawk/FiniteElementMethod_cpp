#include "headers/Grid.h"
#include "headers/Parser.h"
#include "headers/SOE.h"

// Test1_4_4.txt
// Test2_4_4_MixGrid.txt
// Test3_31_31_kwadrat.txt

int main() {
    Grid grid;
    Parser::parseFile("../mesh/Test2_4_4_MixGrid.txt", grid, false);
    grid.calculateAll(2);
    grid.print();

    SOE solver = SOE(grid.getNodes().size());
    auto solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
    std::cout << std::endl << std::endl;

    solution = solver.solve(grid);
    for(auto sol: solution) {
        std::cout << sol << " ";
    }
//    solver.generate_vtk(grid, "Square");

    return 0;
}