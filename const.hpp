#ifndef CONST_HPP
#define CONST_HPP
enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};
std::string const typeStr[] = {"Int8", "Int16", "Int32", "Float", "Double"};
std::string const instructions[11] = {"push",
									  "pop",
									  "dump",
									  "assert",
									  "add",
									  "sub",
									  "mul",
									  "div",
									  "mod",
									  "print",
									  "exit"};
#endif