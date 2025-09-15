#ifndef BIGIINT_HPP
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
    Bigint(unsigned int num);
    Bigint(const Bigint& sourc);
    Bigint& operator=(const Bigint& sourc);
    ~Bigint();

    std::string getStr() const;
};

std::ostream& operator<<(std::ostream& out, const Bigint& obj);





#endif

