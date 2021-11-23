#pragma once
#include "Node.h"
template<class T>
class ConnectedList {
	friend class Node<T>;
private:

	Node<T>* head, *tail;
	Node<T>* prev, *curr, *next;

	size_t lenght;
	int pos;

public:

	ConnectedList() : head(NODE_NULL), tail(NODE_NULL), prev(NODE_NULL)
		, curr(NODE_NULL), next(NODE_NULL), lenght(0), pos(-1) {}
	
	size_t size() const { return this->lenght; }
	bool isEmpty() const { return this->lenght == 0 ? true : false; }
	int position() const { return this->pos; }
	T& data() { return this->curr->data; }

	void reset(int pos = 0);
	void _Next();
	void _Back();
	bool isEndOfList() const { return this->curr->next == NODE_NULL ? false : true; }

	void clear();

};
