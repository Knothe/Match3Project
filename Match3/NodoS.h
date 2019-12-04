#pragma once
#include <iostream>

template<class T>
class NodoS
{
public:
	T value;
	NodoS* next;
	NodoS();
	NodoS(T val);
	~NodoS();
};

template<class T>
NodoS<T>::NodoS() {
	next = NULL;
}

template<class T>
NodoS<T>::NodoS(T val) {
	next = NULL;
	value = val;
}

template<class T>
NodoS<T>::~NodoS() {
}

