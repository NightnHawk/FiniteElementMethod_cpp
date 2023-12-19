//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_PARSER_H
#define FEM_PARSER_H


#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "Element.h"
#include "Node.h"
#include "GlobalData.h"
#include "Grid.h"

class Parser {

public:
    static std::string getLastWord(const std:: string &line);

    static void parseFile(const std::string &path, Grid &grid, bool print=false);
};


#endif //FEM_PARSER_H
