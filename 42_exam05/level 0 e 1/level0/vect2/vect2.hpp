#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2 {
private:
	int _x;
	int _y;

public:
	/* Forma canônica */
	vect2();                      // {0, 0}
	vect2(int x, int y);          // {x, y}
	vect2(const vect2& other);
	~vect2();
	vect2& operator=(const vect2& other);

	/* Acesso por índice (0 -> x, 1 -> y) */
	int& operator[](int idx);          // permite atribuição: v[1] = 42;
	int   operator[](int idx) const;   // leitura em objetos const

	/* Aritméticos básicos */
	vect2  operator+(const vect2& rhs) const;
	vect2  operator-(const vect2& rhs) const;
	vect2& operator+=(const vect2& rhs);
	vect2& operator-=(const vect2& rhs);

	/* Unário menos (negação) */
	vect2 operator-() const;

	/* Escalar (membro) */
	vect2  operator*(int k) const;
	vect2& operator*=(int k);

	/* ++ / -- (pré e pós) */
	// pré-incremento: ++v
	vect2& operator++();     
	// pós-incremento: v++
	vect2  operator++(int);
	// pré-decremento: --v
	vect2& operator--();     
	// pós-decremento: v--
	vect2  operator--(int);

	/* Comparação */
	bool operator==(const vect2& rhs) const;
	bool operator!=(const vect2& rhs) const;
};

/* Escalar (livre): k * v */
vect2 operator*(int k, const vect2& v);

/* Impressão: {x, y} */
std::ostream& operator<<(std::ostream& os, const vect2& v);

#endif /* VECT2_HPP */
