#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <string>
#include <iostream>

class bigint {
public:
    bigint();                       // 0
    bigint(int n);                  // n<0 => 0 (unsigned)
    explicit bigint(const std::string& s);
    bigint(const bigint& o);
    ~bigint();
    bigint& operator=(const bigint& o);

    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const bigint& x) { return os << x.to_string(); }

    bool operator==(const bigint& r) const { return d_ == r.d_; }
    bool operator!=(const bigint& r) const { return !(*this == r); }
    bool operator< (const bigint& r) const;
    bool operator<=(const bigint& r) const { return !(*this > r); }
    bool operator> (const bigint& r) const { return r < *this; }
    bool operator>=(const bigint& r) const { return !(*this < r); }

    bigint  operator+(const bigint& r) const;
    bigint& operator+=(const bigint& r);

    bigint& operator++();     // ++x
    bigint  operator++(int);  // x++

    bigint  operator<<(int n) const;
    bigint  operator>>(int n) const;
    bigint& operator<<=(int n);
    bigint& operator>>=(int n);

    bigint  operator<<(const bigint& n) const;
    bigint  operator>>(const bigint& n) const;
    bigint& operator<<=(const bigint& n);
    bigint& operator>>=(const bigint& n);

private:
    std::vector<int> d_; // base-10, LSB-first (d_[0] unidade)

    void normalize();
    static int  cmpAbs(const bigint& a, const bigint& b);
    static unsigned long to_ul(const bigint& n); // converte com saturação

    void shl_digits(unsigned long k); // *10^k
    void shr_digits(unsigned long k); // /10^k (inteiro)
};

#endif
