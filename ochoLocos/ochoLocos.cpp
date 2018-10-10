#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <cstdlib> 
#include <Windows.h>

using namespace std;

HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
		/*if (c.numero == 1)
			out << "| A ";
		else if (c.numero == 11)
			out << "| J ";
		else if (c.numero == 12)
			out << "| Q ";
		else if (c.numero == 13)
			out << "| K ";
		else
			out << "| " << c.numero << " ";

		out << c.palo << " |";*/
		if (c.palo == char(3) || c.palo == char(4))
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
			if (c.numero == 10)
				out << " " << c.numero;
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
	int nro_el;
public:
	Node<T> *head;
	mazo() : head(NULL), nro_el(0) {};
	T popC();
	bool addC(T carta);
	void print();
	void shuffle();
	void printFirst();
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
	nro_el--;
	return carta;
}


/*Funcion add que agrega una carta en la cima del mazo*/
template <class T>
bool mazo<T>::addC(T carta) {
	Node<T> **p = &head;
	*p = new Node<T>(carta, *p);
	nro_el++;
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

	for (int i = 0; i < nro_el; i++) {
		srand(time(NULL)+i);
		//iteradores
		int j2 = rand() % nro_el;
		int k2 = rand() % nro_el;
		
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

/*Print first.
Solo imprime la carta que este encima del mazo*/
template <class T>
void mazo<T>::printFirst() {
	cout << head->dato << endl;
}

/*Clase Cartasmano:
Sirve para almacenar las cartas en mano que tiene cada jugador*/
template <class T>
class cartasMano {	
public:
	Node<T>*head;
	int num_cartas;
	cartasMano() : head(NULL), num_cartas(0) {};
	bool addCard(T carta);
	T select(int sel);
	void print();
	int getPoints();
	T popC();
};

/*addCard:
Nos ayuda a añadir las cartas que saquemos 
a la mano del jugador*/
template <class T>
bool cartasMano<T>::addCard(T carta){
	Node<T>**p = &head;
	*p = new Node<T>(carta, *p);
	num_cartas++;
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
	num_cartas--;
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
/*getPoitns:
Obtiene el total de puntos del jugador, sumando las cartas
que tiene*/
template <class T>
int cartasMano<T>::getPoints() {
	int puntos = 0;
	for (Node<T>*p = head; p != NULL; p = p->next) {
		if ((p->dato).numero > 10) {
			puntos += 10;
		}
		else if ((p->dato).numero == 8) {
			puntos += 50;
		}
		else {
			puntos += (p->dato).numero;
		}
	}
	cout << puntos << endl;
	return puntos;
}

/*popC: saca la carta de la cima*/
template <class T>
T cartasMano<T>::popC() {
	Node<T> **p = &head;
	Node<T>* temp = *p;
	*p = temp->next;
	T carta = temp->dato;
	delete temp;
	num_cartas--;
	return carta;
}


/*Jugador:
Clase que abstrae al jugador 
tiene como propiedades las cartas que
tiene en mano y sus puntos*/
template <class T>
class Jugador {			
public:
	cartasMano<T> misCartas;
	int puntos;
	string nombre;
	Jugador(string name) : puntos(0), nombre(name) {};
	bool takeCard(T carta);
	T dropCard(int sel);
	void show();
	void getScore();
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
	for (p = head; p->next != head; p = p->next)
		cout << p->dato<<" "<<(p->dato).puntos<<endl;
	cout << p->dato << " " << (p->dato).puntos << endl;
}




class ochoLocos {
public:
	/*Baraja boca abajo*/
	mazo<carta> baraja;
	/*Baraja en mesa (boca arriba)*/
	mazo<carta> mesa;	
	/*Lista de jugadores*/
	listaJugadores<Jugador<carta> > players;
	/*Numero de jugadores*/
	int numJugadores;
	/*Palo actual*/
	char paloActual;
	/*Numero actual*/
	int numeroActual;
	/*Constructor*/
	ochoLocos(int num);
	void reset();
	void run();
};

ochoLocos::ochoLocos(int num) {
	numJugadores = num;
	/*Insertamos todas las cartas en el mazo*/
	char palos[4] = { char(5),char(3),char(6),char(4) };
	//char palos[4] = { 't','c','e','d' };
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 13; j++) {
			baraja.addC(carta(j, palos[i]));
		}
	}
	//baraja.print();	

	/*Las mezclamos*/
	baraja.shuffle();
	/*Funcion para imprimirla*/
	//baraja.print();

	/*Insertamos jugadores en nuestras listas*/
	string nombre;
	for (int i = 0; i < num; i++) {
		cout << "Ingrese nombre jugador " << i+1 << endl;
		cin >> nombre;
		players.addPlayer(nombre);
	}	
}

void ochoLocos::reset() {
	/*Devolvemos todas las cartas en mesa a la baraja*/
	while (mesa.head != NULL) {
		baraja.addC(mesa.popC());
	}
	/*Devolvemos todas las cartas de los jugadores al mazo*/
	DNode<Jugador<carta> > *actual;
	for (actual = players.head; actual->next != players.head; actual = actual->next) {
		while ((actual->dato).misCartas.head != NULL) {
			baraja.addC((actual->dato).misCartas.popC());
		}
		actual->dato.show();
	}

	/*Repartimos las cartas a los jugadores*/
	int totalCartas;
	if (numJugadores == 2)  totalCartas = 7;
	else totalCartas = 8;
	actual = players.head;
	for (int i = 0; i < numJugadores*totalCartas; i++) {
		(actual->dato).takeCard(baraja.popC());
		actual = actual->next;
	}
	/*Ponemos la primera carta de la baraja en la pila de mesa*/
	carta first = baraja.popC();
	while (first.numero == 8) {
		baraja.addC(first);
		baraja.shuffle();
		first = baraja.popC();
	}
	paloActual = first.palo;
	numeroActual = first.numero;
	mesa.addC(first);
	mesa.print();

}

void ochoLocos::run() {
	/*Repartimos las cartas a los jugadores*/
	int totalCartas;
	if (numJugadores == 2)  totalCartas = 7;
	else totalCartas = 8;
	DNode<Jugador<carta> > *actual = players.head;
	for (int i = 0; i < numJugadores*totalCartas; i++) {
		(actual->dato).takeCard(baraja.popC());
		actual = actual->next;
	}

	/*Ponemos la primera carta de la baraja en la pila de mesa*/
	carta first = baraja.popC();
	while (first.numero == 8) {
		baraja.addC(first);
		baraja.shuffle();
		first = baraja.popC();
	}
	paloActual = first.palo;
	numeroActual = first.numero;
	mesa.addC(first);
	mesa.print();
	
	/*Comenzamos el juego con el primer jugador*/
	bool ganar = false;
	while (!ganar) {
		bool finPartida = false;
		actual = players.head;
		int sel = 0;
		while (!finPartida) {
			/*Turno del jugador actual*/
			system("cls");
			bool turno = true;
			/*Mostramos sus cartas*/
			while (turno) {
				/*Imprimimos mesa*/
				cout << "Carta en mesa:" << "\t";
				mesa.printFirst();
				cout << "Turno Jugador: " << actual->dato << endl;
				(actual->dato).show();
				cout << "Palo actual: " << paloActual << endl;
				cout << "Que carta quieres escoger?" << endl;
				cout << "Ingresa el indice de la carta (1 a n)" << endl;
				cout << "Ingresa 0 para tomar una carta" << endl;
				cin >> sel;
				while (sel == 0) {
					if (baraja.head == NULL) {
						finPartida = true;
						cout << "Se acabo el mazo" << endl;
						system("pause");
						break;
					}
					(actual->dato).takeCard(baraja.popC());
					system("cls");
					cout << "Carta en mesa:" << "\t";
					mesa.printFirst();
					cout << "Turno Jugador: " << actual->dato << endl;
					(actual->dato).show();
					cout << "Palo actual: " << paloActual << endl;
					cout << "Que carta quieres escoger?" << endl;
					cout << "Ingresa el indice de la carta (1 a n)" << endl;
					cout << "Ingresa 0 para tomar una carta" << endl;
					cin >> sel;
				}
				while (sel > (actual->dato).misCartas.num_cartas) {
					cout << "Indice de carta inválido, escoge otra" << endl;
					cin >> sel;
				}
				if (baraja.head == NULL) {
					/*Determinar quien gano*/
					DNode<Jugador<carta> >* ganador = players.head;
					DNode<Jugador<carta> >* p;
					for (p = players.head; p->next != players.head; p = p->next) {
						if ((p->dato).misCartas.num_cartas < (ganador->dato).misCartas.num_cartas) {
							ganador = p;
						}
					}
					if ((p->dato).misCartas.num_cartas < (ganador->dato).misCartas.num_cartas) {
						ganador = p;
					}
					/*Sumar puntajes de los jugadores*/
					int puntajeTotal = 0;
					for (p = ganador->next; p != ganador; p = p->next) {
						(p->dato).puntos += (p->dato).misCartas.getPoints();
						puntajeTotal += (p->dato).misCartas.getPoints();
					}
					(ganador->dato).puntos += (puntajeTotal - (ganador->dato).misCartas.getPoints());
					system("cls");
					cout << "Gano jugador: " << ganador->dato << endl;
					players.print();
					system("pause");
					break;
				}
				carta tirada = (actual->dato).dropCard(sel);
				if (tirada.numero == 8) {
					numeroActual = 8;
					char nuevoPalo;
					cout << "Ingrese nuevo palo (t,c,e,d):" << endl;
					cin >> nuevoPalo;
					switch (nuevoPalo)
					{
					case 't':
						nuevoPalo = char(5);
						break;
					case 'c':
						nuevoPalo = char(3);
						break;
					case 'e':
						nuevoPalo = char(6);
						break;
					case 'd':
						nuevoPalo = char(4);
						break;
					}
					paloActual = nuevoPalo;
					mesa.addC(tirada);
					turno = false;
				}
				else if (tirada.numero == numeroActual || tirada.palo == paloActual) {
					numeroActual = tirada.numero;
					paloActual = tirada.palo;
					mesa.addC(tirada);
					turno = false;
				}
				else {
					cout << "No puedes tirar esta carta" << endl;
					(actual->dato).takeCard(tirada);
				}
			}
			if ((actual->dato).misCartas.head == NULL) {
				finPartida = true;
				cout << "Gano jugador " << actual->dato << endl;
				/*Aquí ya se quien gano*/
				DNode<Jugador<carta> >* p;
				/*Sumar puntajes de los jugadores*/
				int puntajeTotal = 0;
				for (p = actual->next; p != actual; p = p->next) {
					(p->dato).puntos += (p->dato).misCartas.getPoints();
					puntajeTotal += (p->dato).misCartas.getPoints();
				}
				(actual->dato).puntos += puntajeTotal;
				system("cls");
				cout << "Gano jugador: " << actual->dato << endl;
				players.print();
				system("pause");
				break;
			}
			actual = actual->next;
		}
		reset();
		/*Determinar si es que hay un ganador*/
		for (actual = players.head; actual->next != players.head; actual = actual->next) {
			if ((actual->dato).puntos >= 50 * numJugadores) {
				system("cls");
				cout << "Ganador total: " << actual->dato << " " << actual->dato.puntos << endl;
				ganar = true;
			}

		}		
	}	
}


int main(){
	int num_players;
	cout << "Ingrese el numero de jugadores, entre 2 y 5" << endl;
	cin >> num_players;
	system("cls");
	ochoLocos mijuego(num_players);
	mijuego.run();
	SetConsoleTextAttribute(hConsole, 15);
	return 0;
}