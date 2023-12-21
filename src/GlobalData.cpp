//
// Created by grzeg on 18.12.2023.
//

#include "../headers/GlobalData.h"

std::map<std::string, int> &GlobalData::getDictionary() {
    return dictionary;
}

const std::vector<double> &GlobalData::getValues() const {
    return values;
}

const double &GlobalData::getValue(int index) const {
    return values[index];
}

void GlobalData::setValues(const std::vector<double> &values) {
    GlobalData::values = values;
}

void GlobalData::setValue(int index, double value) {
    GlobalData::values[index] = value;
}
