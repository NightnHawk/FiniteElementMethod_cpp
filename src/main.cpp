#include "../headers/Grid.h"
#include "../headers/Parser.h"


int main() {
    Grid grid;
    Parser::parseFile("../mesh/Test2_4_4_MixGrid.txt", grid, false);
    grid.calculateAll(2);
    grid.print();



    return 0;
}