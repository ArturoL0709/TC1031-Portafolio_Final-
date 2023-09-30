// =================================================================
//
// Archivo: list.cpp
// Autor:Arturo Lopez Garcia
// Fecha:29/092023
// Complejidad: Búsqueda e inserción en posición específica: O(n)
//Búsqueda de elemento: O(n)
//Eliminación en posición específica: O(n)
//Inserción y eliminación al principio: O(1)
//Inserción y eliminación al final: O(n)
// =================================================================
#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>


template <class T> class List;

// =================================================================
// Definición de la clase Node (Nodo)
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);

	T	    value;
	Node<T> *next;

	friend class List<T>;
};

// =================================================================
// Constructor. Inicializa el valor del nodo. La variable "next"
// se inicializa como nula.
//
// @param val, valor almacenado en el nodo.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

// =================================================================
// Constructor. Inicializa ambas variables de instancia.
//
// @param val, valor almacenado en el nodo.
// @param nxt, el siguiente nodo.
// =================================================================
template <class T>
Node<T>::Node(T val, Node<T>* nxt) : value(val), next(nxt) {
}

// =================================================================
// Definición de la clase List (Lista)
// =================================================================
template <class T>
class List {
private:
	Node<T> *head;
	uint 	size;

public:
	List();
	~List();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    front() const;
	T    last() const;
	T    get(uint) const;

	void push_front(T);
	void push_back(T);
	void insert_at(T, uint);

	T    pop_front();
	T 	 pop_back();
	T    remove_at(uint);

	long int  indexOf(T) const;
};

// =================================================================
// Constructor. Inicializa ambas variables de instancia a cero.
// =================================================================
template <class T>
List<T>::List() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Elimina todos los elementos de la lista.
// =================================================================
template <class T>
List<T>::~List() {
	clear();
}

// =================================================================
// Devuelve si la lista está vacía o no.
//
// @returns true si la lista está vacía, false en caso contrario.
// =================================================================
template <class T>
bool List<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Devuelve el número de elementos en la lista.
//
// @returns size, el número de elementos en la lista.
// =================================================================
template <class T>
uint List<T>::length() const {
	return size;
}

// =================================================================
// Determina si un elemento está en la lista.
//
// @returns true si val está en la lista, false en caso contrario.
// =================================================================
template <class T>
bool List<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Elimina todos los elementos de la lista.
// =================================================================
template <class T>
void List<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// Representación en cadena de caracteres de los elementos en la lista.
//
// @returns una cadena de caracteres que contiene todos los elementos de la lista.
// =================================================================
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Devuelve el primer elemento en la lista.
//
// @returns el objeto T al principio de la lista.
// @throws NoSuchElement, si la lista está vacía.
// =================================================================
template <class T>
T List<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Devuelve el último elemento en la lista.
//
// @returns el objeto T al final de la lista.
// @throws NoSuchElement, si la lista está vacía.
// =================================================================
template <class T>
T List<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Devuelve el elemento en la posición indicada por index.
//
// @returns el elemento en index.
// @throws IndexOutOfBounds, si index >= size.
// =================================================================
template <class T>
T List<T>::get(uint index) const {
	if (index >= size) {
		throw IndexOutOfBounds();
	}

	Node<T> *p = head;
	for (uint i = 0; i < index; i++) {
		p = p->next;
	}

	return p->value;
}

// =================================================================
// Agrega un elemento al principio de la lista. Incrementa el tamaño de
// la lista.
// =================================================================
template <class T>
void List<T>::push_front(T val) {
	Node<T> *q;

	q = new Node<T>(val);
	q->next = head;
	head = q;
	size++;
}

// =================================================================
// Agrega un elemento al final de la lista. Incrementa el tamaño de
// la lista.
// =================================================================
template <class T>
void List<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	p->next = q;
	size++;
}

// =================================================================
// Agrega un elemento en index (0 <= index <= size). El elemento que
// estaba en esa posición se desplaza hacia la derecha.
//
// @throws IndexOutOfBounds, si index > size.
// =================================================================
template <class T>
void List<T>::insert_at(T val, uint index) {
	if (index > size) {
		throw IndexOutOfBounds();
	}

	if (index == 0) {
		push_front(val);
	} else {
		Node<T> *p = head;
		for (uint i = 1; i < index; i++) {
			p = p->next;
		}
		Node<T> *newNode = new Node<T>(val, p->next);
		p->next = newNode;
		size++;
	}
}

// =================================================================
// Elimina el elemento al principio de la lista.
//
// @returns el elemento que estaba al principio de la lista.
// @throws NoSuchElement si la lista está vacía.
// =================================================================
template <class T>
T List<T>::
