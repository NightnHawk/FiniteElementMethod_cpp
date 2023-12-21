//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_GRID_H
#define FEM_GRID_H


#include <vector>
#include "Node.h"
#include "Element.h"
#include "GlobalData.h"

class Grid {
private:
    std::vector<Node> nodes;
    std::vector<Element> elements;
    GlobalData globalData;

public:
    Grid() = default;

    Grid(std::vector<Node> nodes_, std::vector<Element> elements_, GlobalData globalData_) : nodes(nodes_), elements(elements_), globalData(globalData_) {}

    // Getter-y

    GlobalData &getGlobalData();

    std::vector<Node> &getNodes();

    std::vector<Element> &getElements();

    // Setter-y

    void setNodes(const std::vector<Node> &nodes);

    void setElements(const std::vector<Element> &elements);

    void setGlobalData(const GlobalData &globalData);

    void setLocalNodelists();

    // Metody wejścia/wyjścia

    void print();

    // Inne metody

    void calculateAll(int n);
};


#endif //FEM_GRID_H
