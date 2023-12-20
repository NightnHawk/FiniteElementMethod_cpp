//
// Created by grzeg on 18.12.2023.
//

#include "../headers/Node.h"

Node::Node(unsigned int id, double x, double y) : id(id), x(x), y(y), z(0.0), temp(0.0), BC(0) {}

Node::Node(unsigned int id, double x, double y, double z, double temp, unsigned short BC) : id(id), x(x), y(y), z(z), temp(temp), BC(BC) {}

void Node::print() const {
    std::cout << "Node no. " + std::to_string(id) << std::endl;

    std::cout << "Coordinates: " << "( x: " + std::to_string(x) << ", y: " <<
              std::to_string(this->y) << ", z: " << std::to_string(this->z) << " )" << std::endl;

    std::cout << "Temp T: " << std::to_string(temp) << " C" << std::endl;

    std::cout << "BC: " << std::to_string(BC) << std::endl;
}

unsigned int Node::getId() const {
    return id;
}

void Node::setId(unsigned int id_) {
    Node::id = id_;
}

double Node::getX() const {
    return x;
}

void Node::setX(double x_) {
    Node::x = x_;
}

double Node::getY() const {
    return y;
}

void Node::setY(double y_) {
    Node::y = y_;
}

double Node::getZ() const {
    return z;
}

void Node::setZ(double z_) {
    Node::z = z_;
}

double Node::getTemp() const {
    return temp;
}

void Node::setTemp(double temp_) {
    Node::temp = temp_;
}

unsigned short Node::getBc() const {
    return BC;
}

void Node::setBc(unsigned short bc_) {
    BC = bc_;
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os <<  "Node no. " << std::to_string(node.id) << "\nCoordinates: ( x: " << std::to_string(node.x)
    << ", y: " << std::to_string(node.y) << ", z: " << std::to_string(node.z) << ")\nTemp T: "
    << std::to_string(node.temp) << " C\nBC: " << std::to_string(node.BC);
    return os;
}

