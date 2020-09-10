#include "IOperand.hpp"
#include "operandFactory.hpp"
#include "const.hpp"
#include "operand.tpp"
#include <typeinfo>
#include <limits>
OperandFactory::OperandFactory()
{
}

OperandFactory::~OperandFactory()
{
}
IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const
{
    IOperand const *(OperandFactory::*ptrFnc[])(std::string const &) const = {&OperandFactory::createInt8,
                                                                              &OperandFactory::createInt16,
                                                                              &OperandFactory::createInt32,
                                                                              &OperandFactory::createFloat,
                                                                              &OperandFactory::createDouble};
    IOperand const *ret = (this->*ptrFnc[type])(value);
    return ret;
}

IOperand const *OperandFactory::createInt8(std::string const &value) const
{
    int imin = std::numeric_limits<int8_t>::min();
    int imax = std::numeric_limits<int8_t>::max();
    double val = std::stod(value);
    if (val < imin || val > imax)
    {
        throw ErrorAbstract(1, "Overflow detected need to exit");
        // std::cout << "Overflow detected need to exit" << std::endl;
        // exit(0);
    }
    Operand<int8_t> *toRet = new Operand<int8_t>();
    toRet->type = Int8;
    toRet->value = val;
    toRet->str = value;
    toRet->precision = 0;
    return (toRet);
}
IOperand const *OperandFactory::createInt16(std::string const &value) const
{
    int imin = std::numeric_limits<int16_t>::min();
    int imax = std::numeric_limits<int16_t>::max();
    double val = std::stod(value);
    if (val < imin || val > imax)
    {
        throw ErrorAbstract(1, "Overflow detected need to exit");
        // std::cout << "Overflow detected need to exit" << std::endl;
        // exit(0);
    }
    Operand<int16_t> *toRet = new Operand<int16_t>();
    toRet->type = Int16;
    toRet->value = val;
    toRet->str = value;
    toRet->precision = 1;
    return (toRet);
}
IOperand const *OperandFactory::createInt32(std::string const &value) const
{
    int imin = std::numeric_limits<int32_t>::min();
    int imax = std::numeric_limits<int32_t>::max();
    double val = std::stod(value);
    if (val < imin || val > imax)
    {
        throw ErrorAbstract(1, "Overflow detected need to exit");
        // std::cout << "Overflow detected need to exit" << std::endl;
        // exit(0);
    }
    Operand<int32_t> *toRet = new Operand<int32_t>();
    toRet->type = Int32;
    toRet->value = val;
    toRet->str = value;
    toRet->precision = 2;
    return (toRet);
}
IOperand const *OperandFactory::createFloat(std::string const &value) const
{
    int imin = std::numeric_limits<float>::min();
    int imax = std::numeric_limits<float>::max();
    double val = std::stod(value);
    if (val < imin || val > imax)
    {
        throw ErrorAbstract(1, "Overflow detected need to exit");
        // std::cout << "Overflow detected need to exit" << std::endl;
        // exit(0);
    }
    Operand<float> *toRet = new Operand<float>();
    toRet->type = Float;
    toRet->value = val;
    toRet->str = value;
    toRet->precision = 3;
    return (toRet);
}
IOperand const *OperandFactory::createDouble(std::string const &value) const
{
    int imin = std::numeric_limits<double>::min();
    int imax = std::numeric_limits<double>::max();
    double val = std::stod(value);
    if (val < imin || val > imax)
    {
        throw ErrorAbstract(1, "Overflow detected need to exit");
        // std::cout << "Overflow detected need to exit" << std::endl;
        // exit(0);
    }
    Operand<double> *toRet = new Operand<double>();
    toRet->type = Double;
    toRet->value = val;
    toRet->str = value;
    toRet->precision = 4;
    return (toRet);
}