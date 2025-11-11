#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
private:
    int x_;
    int y_;

public:
    // Constructors
    vect2() : x_(0), y_(0) {}
    vect2(int x, int y) : x_(x), y_(y) {}
    vect2(const vect2& o) : x_(o.x_), y_(o.y_) {}

    // Assignment
    vect2& operator=(const vect2& o) {
        if (this != &o) {
            x_ = o.x_;
            y_ = o.y_;
        }
        return *this;
    }

    // Accessors
    int& operator[](int i) { return (i == 0) ? x_ : y_; }
    const int& operator[](int i) const { return (i == 0) ? x_ : y_; }

    // Compound assignments
    vect2& operator+=(const vect2& o) { x_ += o.x_; y_ += o.y_; return *this; }
    vect2& operator-=(const vect2& o) { x_ -= o.x_; y_ -= o.y_; return *this; }
    vect2& operator*=(int k) { x_ *= k; y_ *= k; return *this; }

    // Increment/Decrement (pre)
    vect2& operator++() { ++x_; ++y_; return *this; }
    vect2& operator--() { --x_; --y_; return *this; }

    // Increment/Decrement (post) - non-standard: return new value to match test
   vect2 operator++(int) { 
        vect2 temp = *this;
        ++x_; ++y_;
        return temp;
    }
    vect2 operator--(int) { 
        vect2 temp = *this;
        --x_; --y_;
        return temp;
    }

    // Unary minus
    vect2 operator-() const { return vect2(-x_, -y_); }

    // Comparisons
    bool operator==(const vect2& o) const { return x_ == o.x_ && y_ == o.y_; }
    bool operator!=(const vect2& o) const { return !(*this == o); }

    // Binary operators (friends)
    friend vect2 operator+(const vect2& a, const vect2& b) {
        return vect2(a.x_ + b.x_, a.y_ + b.y_);
    }
    friend vect2 operator-(const vect2& a, const vect2& b) {
        return vect2(a.x_ - b.x_, a.y_ - b.y_);
    }
    friend vect2 operator*(const vect2& v, int k) {
        return vect2(v.x_ * k, v.y_ * k);
    }
    friend vect2 operator*(int k, const vect2& v) {
        return v * k;
    }

    // Output
    friend std::ostream& operator<<(std::ostream& os, const vect2& v) {
        return os << "{" << v.x_ << ", " << v.y_ << "}";
    }
};

#endif
