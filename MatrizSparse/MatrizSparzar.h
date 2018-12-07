#include <iostream>


template <class T>
struct Node {
	T dato;
	Node<T>* left;
	Node<T>* down;
	long i; //Fila
	long j; //Columna
	Node(T d, long i1, long j1) : dato(d), i(i1), j(j1), left(NULL), down(NULL) {};
};

template <class T, T nil>
class MatrizSparza;

template <class T, T nil>
class auxiliar {
public:
	MatrizSparza<T,nil>* m_ms;
	long i, j;
	auxiliar(MatrizSparza<T,nil>* m, long i1, long j1) {
		m_ms = m;
		i = i1;
		j = j1;
	}

	auxiliar operator=(T x) {
		if (x == nil)  m_ms->erase(i,j); 
		else m_ms->insert(x,i,j);
		return *this;
	}
	operator T() {
		Node<T>**p;
		for (p = &(m_ms->rows[i]);
			*p && (*p)->j != this->j;
			p = &((*p)->left));
		if (*p) return (*p)->dato;
		else return nil;
	}

};

template <class T, T nil>
class MatrizSparza {
	Node<T>** rows;
	Node<T>** columns;
	long si, sj;
public:
	MatrizSparza() {
		rows = NULL;
		columns = NULL;
	}
	MatrizSparza(long i, long j) {
		rows = new Node<T>*[i];
		columns = new Node<T>*[j];
		/*Inicializamos todo en nulo*/
		for (long e = 0; e < i; e++) rows[e] = NULL;
		for (long f = 0; f < j; f++) columns[f] = NULL;
		si = i-1;
		sj = j-1;
	}

	bool find(long i1, long j1, Node<T>**&p, Node<T>**&q) {
		/*Hallamos el puntero en las filas*/
		for (p = &rows[i1];
			*p && (*p)->j < j1;
			p = &((*p)->left));

		/*Hallamos el puntero en las columnas*/
		for (q = &columns[j1];
			*q && (*q)->i < i1;
			q = &((*q)->down));

		return (*p == *q) && *p && *q;
	}

	bool insert(T x, long i1, long j1) {
		if (i1 > si || j1 > sj) return 0;
		Node<T>**p, **q;
		if (find(i1, j1, p, q)) {
			(*p)->dato = x;
			return 1;
		}

		Node<T>* aux = new Node<T>(x, i1, j1);

		aux->left = *p;
		*p = aux;
		aux->down = *q;
		*q = aux;
		return 1;
	}

	bool erase(long i1, long j1) {
		if (i1 > si || j1 > sj) return 0;
		Node<T>**p, **q;
		if (!find(i1, j1, p, q)) return 0;
		Node<T>*aux = *p;
		*p = (*p)->left;
		*q = (*q)->down;
		delete aux;
		return 1;
	}

	void print() {
		for (long i = 0; i <= si; i++) {
			Node<T>*p = rows[i];
			while (p) {
				std::cout << p->dato << " " << p->i << " "<<p->j << "\t";
				p = p->left;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void printMT() {
		for (long j = 0; j <= sj; j++) {
			Node<T>*p = columns[j];
			while (p) {
				std::cout << p->dato << " " << p->i << " " << p->j << "\t";
				p = p->down;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}


	/*Sobrecarga del operador*/
	auxiliar<T,nil> operator()(long i, long j) { return auxiliar<T,nil>(this, i, j); }

};

