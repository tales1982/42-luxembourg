#include "Bigint.hpp"


Bigint::Bigint(){}

Bigint::Bigint(int num){
    std::ostringstream out;
    out << num;
    _str = out.str();
}

Bigint::Bigint(const Bigint& other): _str(other._str){}

Bigint& Bigint::operator=(const Bigint& other) {
	if (this != &other)
		this->_str = other._str; 
	return *this;
}

Bigint::~Bigint(){}

const std::string Bigint::getString() const
{
    return _str;
}

std::ostream& operator<<(std::ostream& oss,const Bigint& b)
{
    oss << b.getString();
    return oss;
}

//------------------ OPERADOSRES ---------------------
Bigint& operator+(const Bigint& other, const Bigint& other2)
{
    return other + other2;
}