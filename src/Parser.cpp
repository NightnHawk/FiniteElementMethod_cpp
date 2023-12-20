//
// Created by grzeg on 18.12.2023.
//

#include "../headers/Parser.h"

std::string Parser::getLastWord(const std::string &line) {
    std::istringstream iss(line);
    std::string lastWord, word;

    while (iss >> word)
        lastWord = word;

    return lastWord;
}

void Parser::parseFile(const std::string &path, Grid &grid, bool print) {
    GlobalData globalData;
    bool parsingNodes = false;
    bool parsingElements = false;
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Could not open " + path << std::endl;
        return;
    }

    std::vector<Node> nodes;
    std::vector<Element> elements;
    std::vector<int> bcValues;
    std::string line;
    while (getline(file, line)) {
        if(line.find("*Node") != std::string::npos) {
            parsingNodes = true;
            parsingElements = false;
            continue;
        } else if(line.find("*Element") != std::string::npos) {
            parsingNodes = false;
            parsingElements = true;
            continue;
        } else if(line.find("*BC") != std::string::npos) {
            std::getline(file, line); // Move to the next line after *BC

            // Read the BC values
            std::istringstream bcStream(line);
            std::string bcToken;
            while (std::getline(bcStream, bcToken, ',')) {
                int bcValue = std::stoi(bcToken);
                bcValues.push_back(bcValue);
            }
            break;
        }
        if(!parsingNodes and !parsingElements) {
            for (const auto &pair: globalData.getDictionary()) {
                if(line.find(pair.first) != std::string::npos) {
                    if(print)
                        std::cout << "Found key: " << pair.first << "\t" << getLastWord(line) << std::endl;
                    globalData.setValue(globalData.getDictionary()[pair.first], stod(getLastWord(line)));
                }
            }
        } else if(parsingNodes) {
            std::istringstream iss(line);
            std::string token;

            // Parsing the comma-separated values for node data
            std::getline(iss, token, ','); // Read id
            int id = std::stoi(token);

            std::getline(iss, token, ','); // Read x-coordinate
            double x = std::stod(token);

            std::getline(iss, token); // Read y-coordinate
            double y = std::stod(token);

            // Assuming z-coordinate and temp are default initialized to 0
            double init = globalData.getValue(static_cast<int>(Simulation::InitialTemp));
            Node newNode(id, x, y, 0.0, init, NULL); // Create a new Node object
            nodes.push_back(newNode); // Add the Node to the vector

            if(print)
                newNode.print();

        } else if(parsingElements) {
            std::istringstream iss(line);
            std::string token;

            int id;
            std::vector<int> elementIDs;

            iss >> id;
            elementIDs.push_back(id);

            while (std::getline(iss, token, ',')) {
                if (std::stringstream(token) >> id) {
                    elementIDs.push_back(id);
                }
            }

            // Ensure there are at least 5 IDs for a valid Element
            if (elementIDs.size() >= 5) {
                Element newElement(elementIDs[0], {elementIDs[1], elementIDs[2], elementIDs[3], elementIDs[4]});
                elements.push_back(newElement);

                if(print)
                    newElement.print();
            }
        }
    }

    for(int index: bcValues)
        nodes[index - 1].setBc(1);

    grid.setNodes(nodes);
    grid.setElements(elements);
    grid.setGlobalData(globalData);

    file.close();
}
