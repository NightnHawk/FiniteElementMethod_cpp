cmake_minimum_required(VERSION 3.26)
project(FEM)

set(CMAKE_CXX_STANDARD 23)

add_executable(FEM src/main.cpp
        headers/Matrix.h
        src/Node.cpp
        headers/Node.h
        src/Element.cpp
        headers/Element.h
        src/UniversalElement.cpp
        headers/UniversalElement.h
        src/Surface.cpp
        headers/Surface.h
        src/GaussLegendre.cpp
        headers/GaussLegendre.h
        src/ShapeFunction.cpp
        headers/ShapeFunction.h
        src/Parser.cpp
        headers/Parser.h
        src/GlobalData.cpp
        headers/GlobalData.h
        src/Grid.cpp
        headers/Grid.h
        SOE.cpp
        SOE.h
)
