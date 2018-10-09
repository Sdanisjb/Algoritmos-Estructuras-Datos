#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <windows.h>

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;
//Clase carta
class carta {
public:
	/*La carta tiene un numero y un palo que lo identifica*/
	int numero;
	char palo;
	/*Constructores padrón y con parámetros*/
	carta(int a, char b): numero(a), palo(b){};
	carta() : numero(0), palo('0') {};

	/*Sobrecarga del operador <<*/
	friend ostream & operator << (ostream& out, const carta &c) {
		
		if(c.palo==char(3) || c.palo==char(4))
		    SetConsoleTextAttribute(hConsole, 36);
		else
		    SetConsoleTextAttribute(hConsole, 32);
		
		out << "| " << c.palo;

		if (c.numero == 1)
			out << " A ";
		else if (c.numero == 11)
			out << " J ";
		else if (c.numero == 12)
			out << " Q ";
		else if (c.numero == 13)
			out << " K ";
		else
		{
		    if(c.numero==10)
			out << " " << c.numero ;
		    else
			out << " " << c.numero << " ";
		}

		cout << " |";
		return out;
	}
};



/*Clase nodo:
Nos permitirá implementar listas enlazadas para las cartas*/
template <class T>
class Node {
public:
	T dato;
	Node<T>* next;

	Node(T x, Node<T> *p = NULL) {
		dato = x;
		next = p;
	}
};

/*Clase mazo:
Funciona como una pila (así funcionan todos los mazos)
de manera que la insercion es al comienzo, y solo se puede
sacar una carta de arriba*/
template <class T>
class mazo {
	Node<T> *head;
public:
	mazo() { head = NULL; }
	T popC();
	bool addC(T carta);
	void print();
	void shuffle();
};

/*Función pop para sacar la carta que
este encima del mazo*/
template <class T>
T mazo<T>::popC() {
	Node<T> **p = &head;
	Node<T>* temp = *p;
	*p = temp->next;
	T carta = temp->dato;
	delete temp;
	return carta;
}


/*Funcion add que agrega una carta en la cima del mazo*/
template <class T>
bool mazo<T>::addC(T carta) {
	Node<T> **p = &head;
	*p = new Node<T>(carta, *p);
	return 1;
}

/*Funcion para imprimir todo el mazo*/
template <class T>
void mazo<T>::print() {
	Node<T>*p = head;
	while (p) {
		cout << p->dato << " ";
		p = p->next;
	}
	cout << endl;

}

/*Funcion para mezclar el mazo*/
template <class T>
void mazo<T>::shuffle() {	

	for (int i = 0; i < 52; i++) {
		srand(time(NULL)+i);
		//iteradores
		int j2 = rand() % 52;
		int k2 = rand() % 52;
		
		int j, k;
		//Punteros a nodos
		Node<T>*p = head;
		Node<T>*q = head;
		//Hacemos bucles
		for (p = head, j = 0; j < j2; j++, p = p->next);
		for (q = head, k = 0; k < k2; k++, q = q->next);
		//Hacemos el intercambio
		
		T aux = p->dato;
		p->dato = q->dato;
		q->dato = aux;
		
	}
}

/*Clase Cartasmano:
Sirve para almacenar las cartas en mano que tiene cada jugador*/
template <class T>
class cartasMano {
	Node<T>*head;
public:
	cartasMano() { head = NULL; }
	bool addCard(T carta);
	T select(int sel);
	void print();
};

/*addCard:
Nos ayuda a añadir las cartas que saquemos 
a la mano del jugador*/
template <class T>
bool cartasMano<T>::addCard(T carta){
	Node<T>**p = &head;
	*p = new Node<T>(carta, *p);
	return 1;
}

/*Select:
Nos permite seleccionar la posicion de la carta que
queremos achar a la mesa*/
template <class T>
T cartasMano<T>::select(int sel) {
	Node<T>**p;
	int i;
	for (p = &head, i=1;
		i < sel;
		i++, p = &((*p)->next));
	Node<T>*temp = *p;
	*p = temp->next;
	T carta = temp->dato;
	delete temp;
	return carta;
}

/*print:
Funcion para imprimir todas las cartas en mano*/
template <class T>
void cartasMano<T>::print() {
	for (Node<T>*p = head;
		p != NULL;
		p = p->next) cout << p->dato << " ";

	cout << endl;
}


/*Jugador:
Clase que abstrae al jugador 
tiene como propiedades las cartas que
tiene en mano y sus puntos*/
template <class T>
class Jugador {	
	cartasMano<T> misCartas;	
public:
	int puntos;
	string nombre;
	Jugador(string name) : puntos(0), nombre(name) {};
	bool takeCard(T carta);
	T dropCard(int sel);
	void show();
	int viewPoints();

	/*Sobrecarga de cout para imprimir los nombres de los jugadores*/
	friend ostream & operator << (ostream& out, const Jugador &j) {
		out << j.nombre;
		return out;
	}
};


/*Take card:
Funcion que añade una carta a la
mano del jugador*/
template <class T>
bool Jugador<T>::takeCard(T carta) {
	misCartas.addCard(carta);
	return 1;
}

/*dropCard:
Funcion que quita una carta del mazo del jugador
para ponerla en mesa*/
template <class T>
T Jugador<T>::dropCard(int sel) {
	T carta = misCartas.select(sel);
	return carta;
}

/*Show:
Muestra todas las cartas del jugador*/
template <class T>
void Jugador<T>::show() {
	misCartas.print();
}



/*Dnode:
Nodo doblemente enlazado, surge esta necesidad,
ya que puede cambiar el sentido en el que juegan los jugadores*/
template <class T>
class DNode {
public:
	T dato;
	DNode* prev;
	DNode* next;
	/*Constructor del nodo doblemente enlazado*/
	DNode(T x, DNode<T> *ant, DNode<T> *sig) : dato(x), prev(ant), next(sig) {};
};

/*Lista Jugadores:
Lista donde almacenamos los jugadores
es doblemente enlazada, ya que el orden de juego
puede variar*/
template <class T>
class listaJugadores {	
public:
	DNode<T>*head;
	DNode<T>* tail;
	listaJugadores() :head(NULL), tail(NULL) {};
	bool addPlayer(string name);
	void print();
};

/*addPlayer:
Añade un nuevo jugador, siempre al final de la lista
Los jugadores deben insertarse en el orden de juego*/
template <class T>
bool listaJugadores<T>::addPlayer(string name) {
	T nuevo(name);
	if (!head) {
		head = new DNode<T>(nuevo, 0, 0);
		head->next = head;
		head->prev = head;
		tail = head;
		return 1;
	}
	else {
		DNode<T> *t = new DNode<T>(nuevo, tail, 0);
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
}

/*print:
Imprime los nombres de todos los jugadores*/
template <class T>
void listaJugadores<T>::print() {
	DNode<T>*p;
	for (p = head; p->next != head; p = p->next) cout << p->dato << "\t";
	cout << p->dato << endl;
	DNode<T>*q;
	for (q = tail; q->prev != tail; q = q->prev) cout << q->dato << "\t";
	cout << q->dato << endl;
}


class ochoLocos {
public:
	/*Baraja boca abajo*/
	mazo<carta> baraja;
	/*Baraja en mesa (boca arriba)*/
	mazo<carta> mesa;	
	/*Lista de jugadores*/
	listaJugadores<Jugador<carta> > players;

	/*Constructor*/
	ochoLocos(int num);
};

ochoLocos::ochoLocos(int num) {
	/*Insertamos todas las cartas en el mazo*/
	char palos[4] = { 't','c','e','d' };
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++) {
			baraja.addC(carta(j, palos[i]));
		}
	}
	baraja.print();	

	/*Las mezclamos*/
	baraja.shuffle();
	baraja.print();

	/*Insertamos jugadores en nuestras listas*/
	for (int i = 0; i < num; i++) {
		players.addPlayer("A");
	}
	
	/*Repartimos las cartas a los jugadores*/
	int totalCartas;
	if (num == 2)  totalCartas = 7;
	else totalCartas = 8;
	DNode<Jugador<carta> > *actual = players.head;
	for (int i = 0; i < num*totalCartas; i++) {
		(actual->dato).takeCard(baraja.popC());		
		actual = actual->next;
	}
	actual = players.head;
	while (actual->next != players.head) {
		(actual->dato).show();
		actual = actual->next;
	}
	(actual->dato).show();	
}

int main(){

	ochoLocos mijuego(5);
	
	SetConsoleTextAttribute(hConsole, 15);
	return 0;
}
