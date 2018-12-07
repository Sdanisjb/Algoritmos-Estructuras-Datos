#include <iostream>
#include "linkedList.h"

/*Funcion Dispersion*/
template <class T>
class Dispersion {
public:
	int operator()(T x, long N) { return x % N; }
};

/*Adaptador de la clase*/
//template <class T,class C>
class AdaptorLList : public linkedList<int, menor<int> > {
public:
	bool ins(int x) { return insert(x); }
	bool rem(int x) { return erase(x); }
	void show() { print(); }
};



template <class T, class F, class C, long N>
class HashTable {
	C m_t[N];
	F disp;
public:
	void insert(T x) { m_t[disp(x, N)].ins(x); }
	void erase(T x) { m_t[disp(x, N)].rem(x); }
	void print() {
		for (long i = 0; i < N; i++) {
			m_t[i].show();
		}
	}
};
