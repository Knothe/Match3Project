#pragma once
#include "NodeL.h"

template <class T>
class List
{
private:
public:
	NodeL<T>* first;
	NodeL<T>* last;
	int size;
	List();
	~List();

	void push_back(T val);
	void delete_at(int index);
	T get_at(int index);
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
void List<T>::delete_at(int index) {
	if (size > 0 && index < size) {
		if (index == 0) {
			if (first == last) {
				first = NULL;
				last = NULL;
			}
			else {
				first = first->next;
				_update_index(false, first);
			}
		}
		else {
			NodeL<T>* it = _get_prev(index);
			if (it != NULL) {
				NodeL<T>* n = it->next;
				if (n == last) {
					it->next = NULL;
					last = it;
				}
				else {
					it->next = n->next;
					_update_index(false, it->next);
				}
			}
		}
		size--;
	}
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
