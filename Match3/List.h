#pragma once
#include "NodeL.h"

template <class T>
class List
{
public:
	NodeL<T>* first;
	NodeL<T>* last;
	void Add(List<T>* l);
	int size;
	List();
	~List();
	void clear();
	void push_back(T val);
	T get_at(int index);
	bool find(T val);

};
template <class T>
List<T>::List() {
	first = NULL;
	last = NULL;
	size = 0;
}
template <class T>
List<T>::~List() {

}
template <class T>
void List<T>::push_back(T val) {
	if (!first) {
		first = new NodeL<T>(val, 0);
		last = first;
	}
	else {
		last->next = new NodeL<T>(val, size);
		last = last->next;
	}
	size++;
}
template <class T>
T List<T>::get_at(int index) {
	NodeL<T>* it = first;
	while (it != NULL) {
		if (it->index == index)
			return it->value;
		it = it->next;
	}
	return NULL;
}
template<class T>
void List<T>::clear() {
	first = NULL;
	last = NULL;
	size = 0;
}
template<class T>
bool List<T>::find(T val) {
	NodeL<T>* it = first;
	while (it != NULL) {
		if (it->value == val)
			return true;
		it = it->next;
	}
	return false;
}
template<class T>
void List<T>::Add(List<T>* l) {
	for (int i = 0; i < l->size; i++) {
		push_back(l->get_at(i));
	}
}
