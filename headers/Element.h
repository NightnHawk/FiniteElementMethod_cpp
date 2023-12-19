//
// Created by grzeg on 18.12.2023.
//

#ifndef FEM_ELEMENT_H
#define FEM_ELEMENT_H


#include <utility>
#include <vector>
#include "Matrix.h"
#include "UniversalElement.h"
#include "Node.h"
#include "Surface.h"

class Element {
private:
    unsigned int id;
    std::vector<int> IDs;
    std::vector<Node> nodes;
    std::vector<int> BC_flags;
    std::vector<double> P_vector;
    Matrix<double> H_matrix;
    Matrix<double> Hbc_matrix;
    Matrix<double> C_matrix;

public:
    Element() = default;

    Element(unsigned int id, std::vector<int>IDs);

    std::vector<Matrix<double>> jacobian(UniversalElement universalElement, std::vector<Node> nodes);

    std::pair<Matrix<double>, Matrix<double>> get_dNdi(UniversalElement universalElement, Matrix<double> jacobianMatrix);

    void calculate_H(UniversalElement universalElement,  std::vector<Matrix<double>> jacobianSet, double k);

    double calculate_distance(Node node1, Node node2);

    void calculate_BC(UniversalElement universalElement, double alpha, double t_amb);

    void calculate_C(UniversalElement universalElement, std::vector<Matrix<double>> jacobianSet, double c, double rho);

    void print();

    unsigned int getId() const;

    void setId(unsigned int id);

    const std::vector<int> &getIDs() const;

    void setIDs(const std::vector<int> &iDs);

    const std::vector<Node> &getNodes() const;

    void setNodes(const std::vector<Node> &nodes);

    void appendNode(const Node& node);

    const std::vector<int> &getBcFlags() const;

    void setBcFlags(const std::vector<int> &bcFlags);

    void appendBcFlag(const int &bcFlag);

    const std::vector<double> &getPVector() const;

    void setPVector(const std::vector<double> &pVector);

    const Matrix<double> &getHMatrix() const;

    void setHMatrix(const Matrix<double> &hMatrix);

    const Matrix<double> &getHbcMatrix() const;

    void setHbcMatrix(const Matrix<double> &hbcMatrix);

    const Matrix<double> &getCMatrix() const;

    void setCMatrix(const Matrix<double> &cMatrix);
};


#endif //FEM_ELEMENT_H
