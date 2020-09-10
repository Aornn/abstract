#ifndef ABSTRACT_CLASS_H
#define ABSTRACT_CLASS_H

#include <iostream>

class abstract
{
public:
    abstract();
    ~abstract();
    void getName() const;
    void setName(std::string name);
    void getCpt() const;
    void setCpt(int newCpt);
    int ope(int rhs);

private:
    std::string name;
    int cpt;
};
#endif