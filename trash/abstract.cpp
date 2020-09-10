#include"abstract.hpp"
#include <iostream>
abstract::abstract(void) {}
abstract::~abstract(void) {}

void abstract::setName(std::string name) {
    this->name = name;
}

void abstract::getName() const{
    std::cout << this->name;
}