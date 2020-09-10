#include <exception>
#include <string>

class ErrorAbstract : public std::exception
{
private:
    int value;
    std::string msg;

public:
    ErrorAbstract(int m_value, std::string m_msg)
    {
        value = m_value;
        msg = m_msg;
    }
    ~ErrorAbstract() throw(){};

    std::string getMsg()
    {
        return msg;
    }

    int getValue()
    {
        return value;
    }
};