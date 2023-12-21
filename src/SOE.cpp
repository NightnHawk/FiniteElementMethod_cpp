//
// Created by grzeg on 19.12.2023.
//

#include "../headers/SOE.h"

std::vector<double> SOE::solve(Grid &grid) {
    soe.full(0.0);
    int lastIndex = soe.getRow(0).size() - 1;
    for(const auto &element: grid.getElements()) {
        auto H_ = element.getHMatrix() + element.getHbcMatrix() + element.getCMatrix() * (1.0 / grid.getGlobalData().getValue(
                static_cast<int>(Simulation::SimulationStepTime)));

        for(int i = 0; i < 4; i++) {
            std::vector<double> element_temp;
            for(int j = 0; j < element.getIDs().size(); j++) {
                int id = element.getIDs()[j] - 1;;
                element_temp.emplace_back(grid.getNodes()[id].getTemp());
            }

            soe(element.getIDs()[i] - 1, lastIndex) += element.getPVector()[i] + (element.getCMatrix() * (1.0 / grid.getGlobalData().getValue(
                    static_cast<int>(Simulation::SimulationStepTime))) * element_temp)[i];

            for(int j = 0; j < 4; j++)
                soe(element.getIDs()[i] - 1, element.getIDs()[j] - 1) += H_(i, j);
        }
    }

    auto result = Matrix<double>::gaussJordan(soe);

    for(int i = 0; i < result.size(); i++) {
        grid.getNodes()[i].setTemp(result[i]);
    }

    return result;
}

void SOE::generate_vtk(Grid &grid, std::string nameSchema) {
    int nNodes = grid.getGlobalData().getValue(static_cast<int>(Simulation::Nodes));
    int nElements = grid.getGlobalData().getValue(static_cast<int>(Simulation::Elements));
    double d_tau = grid.getGlobalData().getValue(static_cast<int>(Simulation::SimulationStepTime));
    double t = grid.getGlobalData().getValue(static_cast<int>(Simulation::SimulationTime));
    unsigned int iter_max = (t / d_tau) + 1;
    for(int i = 0; i < iter_max; i++) {
        auto nodes = grid.getNodes();
        auto elements = grid.getElements();
        std::filesystem::create_directories("../vtk/" + nameSchema);
        std::ofstream newFile("../vtk/" + nameSchema + "/" + nameSchema + "_" + std::to_string(i) + ".vtk");
        newFile << "# vtk DataFile Version 2.0" << std::endl;
        newFile << "Unstructured Grid Example" << std::endl;
        newFile << "ASCII" << std::endl;
        newFile << "DATASET UNSTRUCTURED_GRID" << std::endl << std::endl;
        newFile << "POINTS " << std::to_string(nNodes) << " float" << std::endl;
        for(int j = 0; j < nNodes; j++) {
            newFile << nodes[j].getX() << " " << nodes[j].getY() << " " << nodes[j].getZ() << std::endl;
        }
        newFile << std::endl << "CELLS " << std::to_string(nElements) << " " << std::to_string(nElements * 5) << std::endl;
        for(int j = 0; j < nElements; j++) {
            newFile << "4 " << elements[j].getIDs()[0] - 1 << " " << elements[j].getIDs()[1] - 1 << " " << elements[j].getIDs()[2] - 1 << " " << elements[j].getIDs()[3] - 1 << std::endl;
        }
        newFile << std::endl << "CELL_TYPES " << std::to_string(nElements) << std::endl;
        for(int j = 0; j < nElements; j++) {
            newFile << "9" << std::endl;
        }
        newFile << std::endl << "POINT_DATA " << std::to_string(nNodes) << std::endl << "SCALARS Temp float 1" << std::endl << "LOOKUP_TABLE default" << std::endl;
        for(int j = 0; j < nNodes; j++) {
            newFile << std::to_string(nodes[j].getTemp()) << std::endl;
        }
        newFile.close();
        solve(grid);
    }
}
