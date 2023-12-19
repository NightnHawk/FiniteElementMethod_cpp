//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_NODE_H
#define FEM_NODE_H


#include <iostream>

class Node {
private:
    unsigned int id;
    double x;
    double y;
    double z;
    double temp;
    unsigned short BC;

public:
    Node() = default;

    Node(unsigned int id, double x, double y);

    Node(unsigned int id, double x, double y, double z, double temp, unsigned short BC);

    // Output

    void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Node &node);

    // Getters

    [[nodiscard]] unsigned int getId() const;

    [[nodiscard]] double getX() const;

    [[nodiscard]] double getY() const;

    [[nodiscard]] double getZ() const;

    [[nodiscard]] double getTemp() const;

    [[nodiscard]] unsigned short getBc() const;

    // Setters

    void setId(unsigned int id_);

    void setX(double x_);

    void setY(double y_);

    void setZ(double z_);

    void setTemp(double temp_);

    void setBc(unsigned short bc_);
};


#endif //FEM_NODE_H
