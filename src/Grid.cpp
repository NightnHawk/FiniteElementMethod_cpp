//
// Created by grzeg on 18.12.2023.
//

#include "../headers/Grid.h"

void Grid::setLocalNodelists() {
    for(int i = 0; i < this->elements.size(); i++)
        for(int j = 0; j < 4; j++)
            this->elements[i].appendNode(this->nodes[this->elements[i].getIDs()[j]-1]);

    for(int i = 0; i < this->elements.size(); i++) {
        std::vector<int> bc_list = std::vector(4, 0);

        for(int j = 0; j < 4; j++) {
            if(this->elements[i].getNodes()[j].getBc() == 1) {
                bc_list[j] = 1;
            }
        }

        if(bc_list[0] == 1 and bc_list[1] == 1) elements[i].appendBcFlag(0);
        if(bc_list[1] == 1 and bc_list[2] == 1) elements[i].appendBcFlag(1);
        if(bc_list[2] == 1 and bc_list[3] == 1) elements[i].appendBcFlag(2);
        if(bc_list[3] == 1 and bc_list[0] == 1) elements[i].appendBcFlag(3);
    }
}

void Grid::calculateAll(int n) {
    UniversalElement universalElement = UniversalElement(n);
    setLocalNodelists();
    for(int i = 0; i < elements.size(); i++) {
        auto jacob =  elements[i].jacobian(universalElement, elements[i].getNodes());
        elements[i].calculate_H(universalElement, jacob, globalData.getValue(
                static_cast<int>(Simulation::Conductivity)));
        elements[i].calculate_BC(universalElement, globalData.getValue(static_cast<int>(Simulation::Alfa)), globalData.getValue(
                static_cast<int>(Simulation::Tot)));
        elements[i].calculate_C(universalElement, jacob, globalData.getValue(
                static_cast<int>(Simulation::SpecificHeat)), globalData.getValue(
                static_cast<int>(Simulation::Density)));
    }
}

std::vector<Node> &Grid::getNodes() {
    return nodes;
}

void Grid::setNodes(const std::vector<Node> &nodes) {
    Grid::nodes = nodes;
}

std::vector<Element> &Grid::getElements() {
    return elements;
}

void Grid::setElements(const std::vector<Element> &elements) {
    Grid::elements = elements;
}

void Grid::print() {
    for(auto node: nodes) {
        node.print();
        std::cout << std::endl;
    }
    for(auto element: elements) {
        element.print();
        std::cout << std::endl;
    }
}

GlobalData &Grid::getGlobalData() {
    return globalData;
}

void Grid::setGlobalData(const GlobalData &globalData) {
    Grid::globalData = globalData;
}
