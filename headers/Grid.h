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

    void setLocalNodelists();

    void calculateAll(int n);

    std::vector<Node> &getNodes();

    void setNodes(const std::vector<Node> &nodes);

    std::vector<Element> &getElements();

    void setElements(const std::vector<Element> &elements);

    GlobalData &getGlobalData();

    void setGlobalData(const GlobalData &globalData);

    void print();
};


#endif //FEM_GRID_H
