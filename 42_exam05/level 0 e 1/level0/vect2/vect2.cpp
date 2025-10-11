#include "vect2.hpp"

vect2::vect2() : _x(0), _y(0) {}

vect2::vect2(int x, int y) : _x(x), _y(y) {}

vect2::vect2(const vect2& other) : _x(other._x), _y(other._y) {}

vect2::~vect2() {}

vect2& vect2::operator=(const vect2& other) {
	if (this != &other) {
		this->_x = other._x;
		this->_y = other._y;
	}
	return *this;
}


int& vect2::operator[](int idx) {
	if (idx == 0) return _x;
	return _y;
}

int vect2::operator[](int idx) const {
	if (idx == 0) return _x;
	return _y;
}


vect2 vect2::operator+(const vect2& rhs) const {
	return vect2(this->_x + rhs._x, this->_y + rhs._y);
}

vect2 vect2::operator-(const vect2& rhs) const {
	return vect2(this->_x - rhs._x, this->_y - rhs._y);
}

vect2& vect2::operator+=(const vect2& rhs) {
	this->_x += rhs._x;
	this->_y += rhs._y;
	return *this;
}

vect2& vect2::operator-=(const vect2& rhs) {
	this->_x -= rhs._x;
	this->_y -= rhs._y;
	return *this;
}

vect2 vect2::operator-() const {
	return vect2(-this->_x, -this->_y);
}


vect2 vect2::operator*(int k) const {
	return vect2(this->_x * k, this->_y * k);
}

vect2& vect2::operator*=(int k) {
	this->_x *= k;
	this->_y *= k;
	return *this;
}

vect2 operator*(int k, const vect2& v) {
	return v * k;
}

vect2& vect2::operator++() {
	++this->_x;
	++this->_y;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 tmp(*this);
	++(*this);
	return tmp;
}

vect2& vect2::operator--() {
	--this->_x;
	--this->_y;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 tmp(*this);
	--(*this);
	return tmp;
}

bool vect2::operator==(const vect2& rhs) const {
	return (this->_x == rhs._x) && (this->_y == rhs._y);
}

bool vect2::operator!=(const vect2& rhs) const {
	return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& os, const vect2& v) {
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}
