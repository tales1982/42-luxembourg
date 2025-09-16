#include "Bigint.hpp"


Bigint::Bigint(): _str("0"){}

Bigint::Bigint(int num): _str()
{
    std::ostringstream oss;
    oss << num ; // converte o inteiro para texto (base 10)
    _str = oss.str(); // salva no membro
}

Bigint::Bigint(const Bigint& other): _str(other._str){}

Bigint& Bigint::operator=(const Bigint& other) {
	if (this != &other)
		this->_str = other._str; 
	return *this;
}

Bigint::~Bigint(){}

const std::string Bigint::getStr() const
{
    return _str;
}

std::ostream& operator<<(std::ostream& out, const Bigint& b) {
	out << b.getStr();
	return out;
}