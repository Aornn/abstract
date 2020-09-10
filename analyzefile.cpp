#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "IOperand.hpp"
#include "operandFactory.hpp"
#include "const.hpp"
#include "error.hpp"

void dumpOnStack(std::vector<const IOperand *> &stack)
{
    std::vector<const IOperand *>::iterator it;

    for (it = stack.begin(); it != stack.end(); it++)
    {
        std::cout << (*it)->toString() << '\n';
    }
    // std::cout << '\n';
}
void addOnStack(std::vector<const IOperand *> &stack)
{
    if ((!stack.empty() && stack.size() == 1) || stack.empty())
        throw ErrorAbstract(1, "Not enough operand on stack");
    stack[0] = stack[0]->operator+((*stack[1]));
    stack.erase(stack.begin() + 1);
}

void subOnStack(std::vector<const IOperand *> &stack)
{
    if ((!stack.empty() && stack.size() == 1) || stack.empty())
        throw ErrorAbstract(1, "Not enough operand on stack");
    stack[0] = stack[0]->operator-((*stack[1]));
    stack.erase(stack.begin() + 1);
}

void mulOnStack(std::vector<const IOperand *> &stack)
{
    if ((!stack.empty() && stack.size() == 1) || stack.empty())
        throw ErrorAbstract(1, "Not enough operand on stack");
    stack[0] = stack[0]->operator*((*stack[1]));
    stack.erase(stack.begin() + 1);
}

void divOnStack(std::vector<const IOperand *> &stack)
{
    if ((!stack.empty() && stack.size() == 1) || stack.empty())
        throw ErrorAbstract(1, "Not enough operand on stack");
    stack[0] = stack[1]->operator/((*stack[0]));
    stack.erase(stack.begin() + 1);
}

void modOnStack(std::vector<const IOperand *> &stack)
{
    if ((!stack.empty() && stack.size() == 1) || stack.empty())
        throw ErrorAbstract(1, "Not enough operand on stack");
    stack[0] = stack[1]->operator%((*stack[0]));
    stack.erase(stack.begin() + 1);
}

void pushOnStack(std::vector<const IOperand *> &stack, const IOperand *toAdd)
{
    stack.insert(stack.begin(), toAdd);
}

void popOnStack(std::vector<const IOperand *> &stack)
{
    if (stack.empty())
        throw ErrorAbstract(1, "Pop on empty stack");
    stack.erase(stack.begin());
}

void assertOnStack(std::vector<const IOperand *> &stack, const IOperand *toCheck)
{
    // std::cout << toCheck->toString() << " | " << stack[0]->toString() << std::endl;
    if (std::stod(toCheck->toString()) != std::stod(stack[0]->toString()))
        throw ErrorAbstract(1, "Assert failed");
}

void printOnStack(std::vector<const IOperand *> &stack)
{
    if (stack[0]->getType() == Int8)
    {
        std::cout << (char)std::stoi(stack[0]->toString()) << std::endl;
    }
    else
        throw ErrorAbstract(1, "Can't print if the type is not INT8");
}

void findValueType(std::string line, std::string &value, eOperandType &type)
{
    size_t posPar = line.find('(') + 1;

    while (line[posPar] != ')')
    {
        value += line[posPar];
        posPar++;
    }
    if (line.find("int8") != std::string::npos)
        type = Int8;
    else if (line.find("int16") != std::string::npos)
        type = Int16;
    else if (line.find("int32") != std::string::npos)
        type = Int32;
    else if (line.find("float") != std::string::npos)
        type = Float;
    else if (line.find("double") != std::string::npos)
        type = Double;
}

void treatInstruction(std::string ins, std::vector<const IOperand *> &stack, std::string line)
{
    OperandFactory facto;
    std::string value = "";
    eOperandType type;
    if (ins == "pop")
        popOnStack(stack);
    else if (ins == "push")
    {
        findValueType(line, value, type);
        const IOperand *toadd = facto.createOperand(type, value);
        pushOnStack(stack, toadd);
    }
    else if (ins == "dump")
        dumpOnStack(stack);
    else if (ins == "assert")
    {
        findValueType(line, value, type);
        const IOperand *tocheck = facto.createOperand(type, value);
        assertOnStack(stack, tocheck);
    }
    else if (ins == "add")
        addOnStack(stack);
    else if (ins == "sub")
        subOnStack(stack);
    else if (ins == "mul")
        mulOnStack(stack);
    else if (ins == "div")
        divOnStack(stack);
    else if (ins == "mod")
        modOnStack(stack);
    else if (ins == "print")
        printOnStack(stack);
    else if (ins == "exit")
        std::cout << "Exit" << std::endl;
}

int treatInput(std::vector<const IOperand *> &stack, std::string line)
{
    std::regex const regexFloat = std::regex("^(push|assert) (float|double)\\(-?[0-9]+(\\.[0-9]+)?\\)");
    std::regex const regexInt = std::regex("^(push|assert) (int8|int16|int32)\\(-?[0-9]+\\)");
    // int known = 0;
    // std::cout << line << '\n';

    if (line == "exit")
        return 1;
    if (line[0] != ';')
    {
        for (int j = 0; j < 11; j++)
        {
            if (line.rfind(instructions[j], 0) == 0)
            {
                // known = 1;
                if (instructions[j] == "push" || instructions[j] == "assert")
                {
                    std::string lineWithoutComm = "";
                    for (int k = 0; line[k] != ')'; k++)
                    {
                        lineWithoutComm += line[k];
                    }
                    lineWithoutComm += ')';
                    // printf("%s\n", lineWithoutComm.c_str());
                    // exit(0);
                    if (!std::regex_match(lineWithoutComm, regexFloat) && !std::regex_match(lineWithoutComm, regexInt))
                        throw ErrorAbstract(1, "Input wrong format : " + line);
                }
                treatInstruction(instructions[j], stack, line);
                return 2;
            }
        }
        // if (known == 0)
        // {
        throw ErrorAbstract(1, "Unknown instruction : " + line);
        // }
    }
    return 3;
}
int main(int argc, char **argv)
{
    std::string line;
    // bool isExitPresent = false;

    // int known = 0;
    // OperandFactory facto;
    std::vector<const IOperand *> stack;
    // if (stack.empty())
    // {
    //     std::cout << "STACK NOT NULL";
    // }
    std::string lineInput;
    std::vector<std::string> vectLineInput;
    int isExitPresent = 0;
    try
    {
        if (argc < 2)
        {
            while (true)
            {
                std::getline(std::cin, lineInput);
                if (lineInput == ";;")
                {
                    for (size_t i = 0; i < vectLineInput.size(); i++)
                    {
                        // 1 = exit; 2 = Instruction OK; 3 = Commentaire
                        int ret = treatInput(stack, vectLineInput[i]);
                        if (ret == 1)
                            isExitPresent = 1;
                        if (ret == 0)
                            return 1;
                    }
                    if (isExitPresent == 0)
                        throw ErrorAbstract(1, "No exit present");
                    else
                        return 0;
                }
                else
                {
                    vectLineInput.push_back(lineInput);
                }
            }
        }
        else
        {
            std::ifstream MyReadFile(argv[1]);
            while (getline(MyReadFile, line))
            {
                // if (treatInput(stack, line) == 0)
                // {
                //     return 1;
                // }
                int ret = treatInput(stack, line);
                if (ret == 1)
                    isExitPresent = 1;
                if (ret == 0)
                    return 1;
            }
            MyReadFile.close();
            // std::cout << "No exit present" << std::endl;
            // return 0;
            if (isExitPresent == 0)
                throw ErrorAbstract(1, "No exit present");
            else
                return 0;
        }
    }
    catch (ErrorAbstract &e)
    {
        std::cerr << e.getMsg() << std::endl;
        return e.getValue();
    }
}
