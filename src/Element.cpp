//
// Created by grzeg on 18.12.2023.
//

#include "../headers/Element.h"

Element::Element(unsigned int id, std::vector<int> IDs) :
    id(id),
    IDs(IDs),
    P_vector(4, 0.0),
    H_matrix(Matrix<double>(4, 4, 0.0)),
    Hbc_matrix(Matrix<double>(4, 4, 0.0)),
    C_matrix(Matrix<double>(4, 4, 0.0)) {}

std::vector<Matrix<double>> Element::jacobian(UniversalElement universalElement, std::vector<Node> nodes) {
    std::pair<std::vector<double>, std::vector<double>> dx;
    std::pair<std::vector<double>, std::vector<double>> dy;
    for (int i = 0; i < universalElement.n * universalElement.n; i++) {
        std::pair<double, double> aux_x(0.0, 0.0);
        std::pair<double, double> aux_y(0.0, 0.0);
        for (int j = 0; j < 4; j++) {
            aux_x.first += universalElement.dNdKsi(i, j) * nodes[j].getX();
            aux_x.second += universalElement.dNdEta(i, j) * nodes[j].getX();
            aux_y.first += universalElement.dNdKsi(i, j) * nodes[j].getY();
            aux_y.second += universalElement.dNdEta(i, j) * nodes[j].getY();
        }
        dx.first.push_back(aux_x.first);
        dx.second.push_back(aux_x.second);
        dy.first.push_back(aux_y.first);
        dy.second.push_back(aux_y.second);
    }

    std::vector<Matrix<double>> jacobianSet;
    for (int k = 0; k < universalElement.n * universalElement.n; k++) {
        Matrix<double> matrix = Matrix<double>(2, 2);
        matrix(0, 0) = dx.first[k]; matrix(0, 1) = dy.first[k];
        matrix(1, 0) = dx.second[k]; matrix(1, 1) = dy.second[k];
        jacobianSet.push_back(matrix);
    }

    return jacobianSet;
}

unsigned int Element::getId() const {
    return id;
}

void Element::setId(unsigned int id) {
    Element::id = id;
}

const std::vector<int> &Element::getIDs() const {
    return IDs;
}

void Element::setIDs(const std::vector<int> &iDs) {
    IDs = iDs;
}

const std::vector<Node> &Element::getNodes() const {
    return nodes;
}

void Element::setNodes(const std::vector<Node> &nodes) {
    Element::nodes = nodes;
}

void Element::appendNode(const Node &node) {
    Element::nodes.emplace_back(node);
}

const std::vector<int> &Element::getBcFlags() const {
    return BC_flags;
}

void Element::setBcFlags(const std::vector<int> &bcFlags) {
    BC_flags = bcFlags;
}

const std::vector<double> &Element::getPVector() const {
    return P_vector;
}

void Element::setPVector(const std::vector<double> &pVector) {
    P_vector = pVector;
}

const Matrix<double> &Element::getHMatrix() const {
    return H_matrix;
}

void Element::setHMatrix(const Matrix<double> &hMatrix) {
    H_matrix = hMatrix;
}

const Matrix<double> &Element::getHbcMatrix() const {
    return Hbc_matrix;
}

void Element::setHbcMatrix(const Matrix<double> &hbcMatrix) {
    Hbc_matrix = hbcMatrix;
}

const Matrix<double> &Element::getCMatrix() const {
    return C_matrix;
}

void Element::setCMatrix(const Matrix<double> &cMatrix) {
    C_matrix = cMatrix;
}

void Element::calculate_H(UniversalElement universalElement, std::vector<Matrix<double>> jacobianSet, double k) {
    std::vector<Matrix<double>> dNdxSet;
    std::vector<Matrix<double>> dNdySet;
    for (auto jacobianInstance: jacobianSet) {
        auto dN = this->get_dNdi(universalElement, jacobianInstance);
        dNdxSet.push_back(dN.first);
        dNdySet.push_back(dN.second);
    }

//    for(auto matrix: dNdxSet) {
//        matrix.print();
//    }

    std::vector<Matrix<double>> H_sub;

    for (int i = 0; i < universalElement.n * universalElement.n; i++) {
        auto H_sub_element = (Matrix<double>::outerProduct(dNdxSet[i].getRow(i), dNdxSet[i].getRow(i)) +
                              Matrix<double>::outerProduct(dNdySet[i].getRow(i), dNdySet[i].getRow(i))) * k * jacobianSet[i].determinant();
        H_sub.push_back(H_sub_element);
    }

    auto gaussLegendre = GaussLegendre::getGaussLegendre(universalElement.n);
    std::vector<double> weights;
    for(auto root: gaussLegendre)
        weights.push_back(root.second);

    Matrix<double> weigths_squared = Matrix<double>::outerProduct(weights, weights);

    std::vector<double> flattened = weigths_squared.flatten();

//    for(int i = 0; i < weigths_squared.numRows(); i++) {
//        flattened.insert(flattened.end(), weigths_squared.getRow(i).begin(), weigths_squared.getRow(i).end());
//    }


    Matrix<double> result(H_sub[0].numRows(), H_sub[0].numCols(), 0.0);

    for(int i = 0; i < universalElement.n * universalElement.n; i++)
        result = result + (H_sub[i] * flattened[i]);

    setHMatrix(result);
}

std::pair<Matrix<double>, Matrix<double>>
Element::get_dNdi(UniversalElement universalElement, Matrix<double> jacobianMatrix) {
    double det_reciprocal = 1.0 / jacobianMatrix.determinant();
    Matrix<double> matrix = Matrix<double>(2, 2);
    matrix(0, 0) = jacobianMatrix(1, 1) * det_reciprocal;
    matrix(0, 1) = -jacobianMatrix(0, 1) * det_reciprocal;
    matrix(1, 0) = -jacobianMatrix(1, 0) * det_reciprocal;
    matrix(1, 1) = jacobianMatrix(0, 0) * det_reciprocal;

    Matrix<double> dNdx(universalElement.n * universalElement.n, 4);
    Matrix<double> dNdy(universalElement.n * universalElement.n, 4);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < universalElement.n * universalElement.n; ++j) {
            dNdx(j, i) = matrix(0, 0) * universalElement.dNdKsi(j, i) + matrix(0, 1) * universalElement.dNdEta(j, i);
            dNdy(j, i) = matrix(1, 0) * universalElement.dNdKsi(j, i) + matrix(1, 1) * universalElement.dNdEta(j, i);
        }
    }

    return std::make_pair(dNdx, dNdy);
}

void Element::appendBcFlag(const int &bcFlag) {
    BC_flags.push_back(bcFlag);
}

double Element::calculate_distance(Node node1, Node node2) {
    return sqrt(pow((node1.getX() - node2.getX()),2) + pow((node1.getY() - node2.getY()),2));
}

void Element::calculate_BC(UniversalElement universalElement, double alpha, double t_amb) {
    double L;
    auto gauss = GaussLegendre::getGaussLegendre(universalElement.n);
    std::vector<double> weights;
    for (auto set : gauss) {
        weights.push_back(set.second);
    }

    std::vector<Matrix<double>> Hbc;
    std::vector<std::vector<double>> P;

    if (BC_flags.empty()) {
        Hbc_matrix = Matrix<double>(4, 4, 0.0);
        P_vector = std::vector<double>(4, 0.0);
    }

    Node node1, node2;
    Surface sur = Surface(universalElement.n);

    for (auto surface : BC_flags) {
        node1 = nodes[surface % 4];
        node2 = nodes[(surface + 1) % 4];
        L = calculate_distance(node1, node2);

        //auto surface_row = sur.surface_tab[surface].getRow(0);

        auto resultHbc = Matrix<double>::outerProduct(sur.surface_tab[surface].getRow(0), sur.surface_tab[surface].getRow(0)) * alpha * weights[0];
        auto resultP = Matrix<double>::vecMultiplyScalar(sur.surface_tab[surface].getRow(0), alpha * weights[0] * t_amb);

        for (int i = 1; i < universalElement.n; i++) {
//                surface_row = sur.surface_tab[surface].getRow(i);
            resultHbc = resultHbc + (Matrix<double>::outerProduct(sur.surface_tab[surface].getRow(i), sur.surface_tab[surface].getRow(i)) * alpha * weights[i]);
            resultP = Matrix<double>::vecSum(resultP,
                                             Matrix<double>::vecMultiplyScalar(sur.surface_tab[surface].getRow(i),
                                                                               alpha * weights[i] * t_amb));
        }

        Hbc.push_back(resultHbc);
        P.push_back(resultP);
    }

    Matrix<double> Hbc_result(4,4, 0.0);
    std::vector<double> P_result(4, 0.0);

    for (auto matrix : Hbc) {
        Hbc_result = Hbc_result + matrix;
    }
    for (auto vec : P) {
        P_result = Matrix<double>::vecSum(P_result, vec);
    }

    setHbcMatrix(Hbc_result * (L / 2.0));
    setPVector(Matrix<double>::vecMultiplyScalar(P_result, L / 2.0));
}

void Element::print() {
    std::cout << "Element no. " << id << std::endl;
    for(auto node: nodes)
        std::cout << node.getId() << "\t( x: " << std::to_string(node.getX()) << ", y: " << std::to_string(node.getY()) << ", z: " << std::to_string(node.getZ()) << " )" << std::endl;
    std::cout << std::endl;
    std::cout << "BC: " << std::endl;
    for(auto bc: BC_flags) {
        std::cout << bc << " ";
    }
    std::cout << std::endl << std::endl;
    std::cout << "H matrix:" << std::endl;
    H_matrix.print();
    std::cout << std::endl;
    std::cout << "Hbc matrix:" << std::endl;
    Hbc_matrix.print();
    std::cout << std::endl;
    std::cout << "C matrix:" << std::endl;
    C_matrix.print();
    std::cout << std::endl;
    std::cout << "P vector:" << std::endl;
    for(auto p: P_vector)
        std::cout << p << " ";
    std::cout << std::endl;
}

void
Element::calculate_C(UniversalElement universalElement, std::vector<Matrix<double>> jacobianSet, double c, double rho) {
    std::vector<Matrix<double>> C_sub;

    for(int i = 0; i < universalElement.n * universalElement.n; i++) {
        auto C_sub_element = Matrix<double>::outerProduct(universalElement.N_matrix.getRow(i), universalElement.N_matrix.getRow(i)) * c * rho * jacobianSet[i].determinant();
        C_sub.push_back(C_sub_element);
    }

    std::vector<std::pair<double, double>> gauss = GaussLegendre::getGaussLegendre(universalElement.n);
    std::vector<double> weights;
    for(auto set: gauss) {
        weights.push_back(set.second);
    }
    Matrix<double> weights_squared = Matrix<double>::outerProduct(weights, weights);

    std::vector<double> flattened = weights_squared.flatten();

    Matrix<double> result(C_sub[0].numRows(), C_sub[0].numCols(), 0.0);
    for(int i = 0; i < universalElement.n * universalElement.n; i++) {
        result = result + (C_sub[i] * flattened[i]);
    }

    setCMatrix(result);
}
