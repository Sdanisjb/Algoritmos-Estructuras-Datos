#include <iostream>
#include "MatrizSparzar.h"
using namespace std;

int main() {

	MatrizSparza<int,0> m_m(3, 3);

	m_m(0, 0) = 1;
	m_m(1, 1) = 5;
	m_m(2, 2) = 9;
	m_m(0, 1) = 2;
	m_m(0, 2) = 3;
	m_m(1, 0) = 4;
	m_m(1, 2) = 6;
	m_m(2, 0) = 7;
	m_m(2, 1) = 8;

	m_m.print();
	//m_m.printMT();
	return 0;
}