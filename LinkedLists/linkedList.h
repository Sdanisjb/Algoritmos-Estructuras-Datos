#include <iostream>

//Clase menor
template <class C>
class menor {
public:
	inline bool operator()(C x, C y) { return x < y; }
};

//Clase mayor
template <class C>
class mayor {
public:
	inline bool operator()(C x, C y) { return x > y; }
};

//Clase nodo
template <class T>
class Node {
public:
	T data;
	Node* next;
	Node(T,Node<T>*);	
};

//Constructor
template <class T>
Node<T>::Node(T x,Node<T>*p) :data(x), next(p) {};



//Clase lista
template <class T, class C>
class linkedList {
	Node<T>* head;
	C comp;
public:
	linkedList();
	bool find(T, Node<T>**&);
	bool insert(T);
	bool erase(T);
	void print();
};

template <class T, class C>
linkedList<T, C>::linkedList() : head (NULL){};

//Funcion buscar
template <class T, class C>
bool linkedList<T, C>::find(T x, Node<T>**&p) {
	for (p = &head;
	*p && comp((*p)->data, x);
	p = &((*p)->next));
	return *p && (*p)->data == x;
}

//Funcion insertar
template <class T, class C>
bool linkedList<T, C>::insert(T x) {
	Node<T>**p;
	if (find(x, p)) return 0;
	*p= new Node<T>(x,*p);
	return 1;
}

//Funcion borrar
template <class T, class C>
bool linkedList<T, C>::erase(T x) {
	Node<T>**p;
	if (!find(x, p)) return 0;
	Node <T>* temp = *p;
	*p = temp->next;
	delete temp;
	return 1;
}

//Funcion imprimir
template <class T, class C>
void linkedList<T, C>::print() {
	Node<T>*p = head;
	while (p) {
		std::cout << p->data << "\t";
		p = p->next;
	}
	std::cout << std::endl;
}

//Lista Doblemente Enlazada

//Nodo
template <class T>
class DNode {
public:
	T data;
	DNode* prev;
	DNode* next;
	DNode(T, DNode<T>*,DNode<T>*);
};

//Constructor DNodo
template <class T>
DNode<T>::DNode(T x, DNode<T>* p, DNode<T>* n) : data(x), prev(p), next(n) {};

//Lista
template <class T, class C>
class DLinkedList {
public:
	DNode<T>* head, *tail;
	C comp;
	
	DLinkedList();
	bool find(T x,DNode<T>**&, DNode<T>**&);
	bool insert(T x);
	bool erase(T x);
	void print();
};

//Constructor
template <class T, class C>
DLinkedList<T,C>::DLinkedList() : head(NULL), tail(NULL) {};

//Funcion Find
template <class T, class C>
bool DLinkedList<T, C>::find(T x, DNode<T>**& p, DNode<T>**& n) {
	for (p = &head;
	*p && comp((*p)->data, x);
	p = &((*p)->next));
	
	for (n = &tail;
	*n && comp(x, (*n)->data);
	n = &((*n)->prev));	
	
	return *p && (*p)->data == x;
}

//Funcion insertar
template <class T, class C>
bool DLinkedList<T, C>::insert(T x) {
	DNode<T>**p;
	DNode<T>**n;
	if (find(x, p, n)) {
		n = &(*p)->prev;
	}
	*p = new DNode<T>(x, *n, *p);	
	*n = *p;
	
	return 1;
}

template <class T, class C>
bool DLinkedList<T, C>::erase(T x) {
	DNode<T>**p, **n;
	if (!find(x, p, n)) return 0;
	DNode <T>* temp = *p;
	*p = temp->next;
	*n = temp->prev;
	delete temp;
	return 1;
}

//Funcion imprimir
template <class T, class C>
void DLinkedList<T, C>::print() {
	DNode<T>*p = head;
	while (p->next) {
		std::cout << p->data <<"\t";
		p = p->next;
	}
	std::cout<< p->data<< std::endl;
	
	while (p->prev) {
		std::cout << p->data << "\t";
		p = p->prev;
	}
	std::cout << p->data << std::endl;
}


//Clase Lista Circular
//Clase lista
template <class T, class C>
class ClinkedList {
	Node<T>* head;
	C comp;
public:
	ClinkedList();
	bool find(T, Node<T>**&);
	bool insert(T);
	bool erase(T);
	void print();
};

template <class T, class C>
ClinkedList<T, C>::ClinkedList() : head(NULL) {};

//Funcion buscar
template <class T, class C>
bool ClinkedList<T, C>::find(T x, Node<T>**&p) {
	for (p = &head;
	comp((*p)->data, x) && (*p)->next != head;
	p = &((*p)->next));
	
	if (comp((*p)->data, x)) p = &((*p)->next);
	
	return (*p)->data == x;
}

//Funcion insertar
template <class T, class C>
bool ClinkedList<T, C>::insert(T x) {	
	if (!head) {
		head = new Node<T>(x, 0);
		head->next = head;
		return 1;
	}	
	Node<T>**p;
	find(x, p);	
	if (comp(x, head->data) || x == head->data) {
		Node<T> *t = new Node<T>(x, head);		
		Node<T> * q;
		for (q = head; q->next != head; q = q->next);
		q->next = t;
		head = t;
		return 1;
	}
	*p = new Node<T>(x, *p);	
	return 1;
}

//Funcion borrar
template <class T, class C>
bool ClinkedList<T, C>::erase(T x) {
	Node<T>**p;
	if (!find(x, p)) return 0;
	if (*p == head) {
		Node<T> * q;
		for (q = head; q->next != head; q = q->next);
		q->next = (*p)->next;
		if ((*p)->next == head) {
			head = 0;
			Node <T>* temp = *p;
			delete temp;
			return 1;
		}
	}
	Node <T>* temp = *p;
	*p = temp->next;
	delete temp;
	return 1;
}

//Funcion imprimir
template <class T, class C>
void ClinkedList<T, C>::print() {
	Node<T>*p = head;
	if (head == NULL) {
		std::cout << std::endl;
		return;
	}
	while (p->next != head) {
		std::cout << p->data << "\t";
		p = p->next;
	}
	std::cout << p->data << std::endl;
}


//Lista
template <class T, class C>
class CDLinkedList {
public:
	DNode<T>* head, *tail;
	C comp;
	
	CDLinkedList();
	bool find(T x, DNode<T>**&, DNode<T>**&);
	bool insert(T x);
	bool erase(T x);
	void print();
};

//Constructor
template <class T, class C>
CDLinkedList<T, C>::CDLinkedList() : head(NULL), tail(NULL) {};

//Funcion Find
template <class T, class C>
bool CDLinkedList<T, C>::find(T x, DNode<T>**& p, DNode<T>**& n) {
	for (p = &head;
	(*p)->next!=head && comp((*p)->data, x);
	p = &((*p)->next));
	
	for (n = &tail;
	(*n)->prev!=tail && comp(x, (*n)->data);
	n = &((*n)->prev));
	
	return (*p)->data == x;
}

//Funcion insertar
template <class T, class C>
bool CDLinkedList<T, C>::insert(T x) {
	if (!head) {
		head = new DNode<T>(x, 0, 0);
		head->next = head;
		head->prev = head;
		tail = head;
		return 1;
	}
	DNode<T>**p;	
	DNode<T>**n;
	find(x, p, n);
	if (comp(x, head->data) || head->data == x) {
		DNode<T> *t = new DNode<T>(x, 0, head);
		DNode<T> *q, *q2;
		for (q = head; q->next != head; q = q->next);
		q->next = t;
		t->prev = q;
		head = t;
		
		for (q2 = tail; q2->prev != tail; q2 = q2->prev);
		q2->prev = t;
		t->next = q2;
		return 1;
	}
	else if (comp(tail->data, x) || tail->data == x) {
		DNode<T> *t = new DNode<T>(x, tail, 0);
		DNode<T> *q, *q2;
		for (q = tail; q->prev != tail; q = q->prev);
		q->prev = t;
		t->next = q;
		tail = t;
		
		for (q2 = head; q2->next != head; q2 = q2->next);
		q2->next = t;
		t->prev = q2;
		return 1;
	}
	*p = new DNode<T>(x, *n, *p);
	*n = *p;
	return 1;
}

template <class T, class C>
bool CDLinkedList<T, C>::erase(T x) {
	DNode<T>**p, **n;
	if (!find(x, p, n)) return 0;
	DNode <T>* temp = *p;
	if (*p == head && (*p)->next == head) {
		head = NULL;
		tail = NULL;
		
		delete temp;
		return 1;
	}
	if (*p == head) {
		DNode<T> *q, *q2;
		for (q = head; q->next != head; q = q->next);
		q->next = (*p)->next;
		
		
		for (q2 = tail; q2->prev != head; q2 = q2->prev);
		q2->prev = (*p)->prev;
		
		head = q->next;
		tail = q2->prev;
		
		delete temp;
		return 1;
	}
	if (*p == tail) {
		DNode<T> *q, *q2;
		for (q = tail; q->prev != tail; q = q->prev);
		q->prev = (*p)->prev;
		
		for (q2 = head; q2->next != tail; q2 = q2->next);
		q2->next = (*p)->next;
		
		tail = q->prev;
		head = q2->next;
		
		delete temp;
		return 1;
	}	
	*p = temp->next;
	*n = temp->prev;
	delete temp;
	return 1;
}

//Funcion imprimir
template <class T, class C>
void CDLinkedList<T, C>::print() {
	DNode<T>*p = head;
	if (p == NULL) {
		std::cout << std::endl;
		return;
	}
	while (p->next != head) {
		std::cout << p->data << "\t";//" "<<p<<" "<<p->next<<" "<<p->prev<<"\t";
		p = p->next;
	}
	std::cout << p->data << std::endl;// " " << p << " " << p->next << " " << p->prev << std::endl;
	
	p = tail;
	while (p->prev != tail) {
		std::cout << p->data << "\t";
		p = p->prev;
	}
	std::cout << p->data << std::endl;
}

//Clase vector
//Forward iterador
template <class T>
class vecFWiterator{
	T* m_i;
public:
	vecFWiterator(T*p = 0):m_i(p){};
	vecFWiterator operator=(vecFWiterator a){
		m_i = a.m_i;
		return *this;
	}
	
	bool operator!=(vecFWiterator a){return m_i != a.m_i;}
	
	vecFWiterator operator++(int){
		m_i++;
		return *this;
	}
	
	T operator*(){return *m_i;}
};

//Reverse iterator
template <class T>
class vecRViterator{
	T* m_i;
public:
	vecRViterator(T*p = 0):m_i(p){};
	vecRViterator operator=(vecRViterator a){
		m_i = a.m_i;
		return *this;
	}
	
	bool operator!=(vecRViterator a){return m_i != a.m_i;}
	
	vecRViterator operator++(int){
		m_i--;
		return *this;
	}
	
	T operator*(){return *m_i;}
};

//Clase en si
template <class T>
class vector{
	T* vec;
	int size;
public:
	vector(int n){
		vec = new T[n];
		size = n;
		for(int i=0;i<n;i++){
			vec[i] = i+1;
		}
	}
	void print(){
		for(int i=0;i<size;i++)
			std::cout<<vec[i]<<" ";
		std::cout<<std::endl;
	}
	//Declaracion del iterador
	typedef vecFWiterator<T> iterator;
	typedef vecRViterator<T> riterator;
	
	//iterator
	iterator begin(){return iterator(vec);}
	iterator end(){return iterator(vec+size);}
	
	//riterator
	riterator rbegin(){return riterator(vec+size-1);}
	riterator rend(){return riterator(vec-1);}
};

