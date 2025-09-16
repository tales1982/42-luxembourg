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
    Bigint();                                   // default
    Bigint(int num);                   // constructor with parametre
    Bigint(const Bigint& other);                // copy ctor
    Bigint& operator=(const Bigint& other);     // copy assign
    ~Bigint();                                  //destructor

    const std::string getStr() const;
};

std::ostream& operator<<(std::ostream& out, const Bigint& obj);





#endif

