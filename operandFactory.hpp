#ifndef OPERAND_FACTORY_HPP
#define OPERAND_FACTORY_HPP

#include <iostream>
#include <string>
#include "IOperand.hpp"

class OperandFactory
{
public:
    OperandFactory();
    ~OperandFactory();
    IOperand const *createOperand(eOperandType type, std::string const &value) const;

private:
    IOperand const *createInt8(std::string const &value) const;
    IOperand const *createInt16(std::string const &value) const;
    IOperand const *createInt32(std::string const &value) const;
    IOperand const *createFloat(std::string const &value) const;
    IOperand const *createDouble(std::string const &value) const;
};

#endif