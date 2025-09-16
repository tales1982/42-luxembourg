#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>

class Bigint
{
private:
    std::string _str;
public:
    Bigint();
    Bigint(int num);
    Bigint(const Bigint& other);
    Bigint& operator=(const Bigint& other);
    ~Bigint();

    const std::string getString() const;


    //operadores
    Bigint& operator+(const Bigint& other);
};

std::ostream& operator<<(std::ostream& oss,const Bigint& b);


#endif