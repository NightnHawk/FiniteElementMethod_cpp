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

    const std::vector<Node> &getNodes() const;

    void setNodes(const std::vector<Node> &nodes);

    const std::vector<Element> &getElements() const;

    void setElements(const std::vector<Element> &elements);

    const GlobalData &getGlobalData() const;

    void setGlobalData(const GlobalData &globalData);

    void print();
};


#endif //FEM_GRID_H
