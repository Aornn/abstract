#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "IOperand.hpp"
#include "operandFactory.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "error.hpp"
template <typename T>
class Operand : public IOperand
{
    // private:
    //     eOperandType type;
    //     T value;
    //     std::string str;
    //     int precision;

public:
    eOperandType type;
    T value;
    std::string str;
    int precision;
    int getPrecision(void) const
    {
        return this->precision;
    }
    eOperandType getType(void) const
    {
        return this->type;
    }
    std::string const &toString(void) const
    {
        return this->str;
    }
    IOperand const *operator+(IOperand const &rhs) const
    {
        OperandFactory s;
        eOperandType newType = this->type;

        double newValue = this->value + std::stod(rhs.toString());
        if (rhs.getPrecision() > this->precision)
            newType = rhs.getType();
        return (s.createOperand(newType, std::to_string(newValue)));
    }
    IOperand const *operator-(IOperand const &rhs) const
    {
        OperandFactory s;
        eOperandType newType = this->type;

        double newValue = this->value - std::stod(rhs.toString());
        if (rhs.getPrecision() > this->precision)
            newType = rhs.getType();
        return (s.createOperand(newType, std::to_string(newValue)));
    }
    IOperand const *operator*(IOperand const &rhs) const
    {
        OperandFactory s;
        eOperandType newType = this->type;

        double newValue = this->value * std::stod(rhs.toString());
        if (rhs.getPrecision() > this->precision)
            newType = rhs.getType();
        return (s.createOperand(newType, std::to_string(newValue)));
    }
    IOperand const *operator/(IOperand const &rhs) const
    {
        OperandFactory s;
        eOperandType newType = this->type;

        std::cout << rhs.toString() << std::endl;
        if (std::stod(rhs.toString()) == 0)
        {
            throw ErrorAbstract(1, "No division by 0");
            // std::cout
            // << "No division by 0" << std::endl;
            // exit(0);
        }
        double newValue = this->value / std::stod(rhs.toString());
        if (rhs.getPrecision() > this->precision)
            newType = rhs.getType();
        return (s.createOperand(newType, std::to_string(newValue)));
    }
    IOperand const *operator%(IOperand const &rhs) const
    {
        OperandFactory s;
        eOperandType newType = this->type;

        if (std::stod(rhs.toString()) == 0)
        {
            throw ErrorAbstract(1, "No modulo by 0");
            // std::cout << "No modulo by 0" << std::endl;
            // exit(0);
        }
        if (rhs.getPrecision() > this->precision)
            newType = rhs.getType();
        double newValue = std::fmod(this->value, std::stod(rhs.toString()));
        return (s.createOperand(newType, std::to_string(newValue)));
    }
};

#endif