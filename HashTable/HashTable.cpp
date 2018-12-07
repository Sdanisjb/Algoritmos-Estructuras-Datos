#include <iostream>
#include "HashTable.h"



using namespace std;

int main() {
	HashTable<int,Dispersion<int>, AdaptorLList, 13> m_h;
	for (int i = 0; i < 14; i++) {
		m_h.insert(i);
	}
	m_h.print();

	return 0;
}