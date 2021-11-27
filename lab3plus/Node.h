#pragma once

template <class T, class T1>
class Node {
#define NODE_NULL static_cast<Node<T, T1>*>(nullptr)
private:

	Node<T>* prev;
	Node<T>* next;
	T data_1;
	T1 data_2;

public:

	~Node() {
		delete prev;
		delete next;
	}
	Node() : data{}, next(NODE_NULL),
		prev(NODE_NULL) {}
	explicit Node(const T& data_1, const T1& data_2, Node<T, T1>* _nextNode = NODE_NULL,
		Node<T>* _prevNode = NODE_NULL) {
		this->data_1 = data_1;
		this->data_2 = data_2;
		this->next = _nextNode; 
		this->prev = _prevNode;
	}
	Node(const Node<T, T1>*& node) { this = node; }

	T& getFirst() { return this->data_1; }
	T1& getSecond() { return this->data_2; }
	Node<T, T1>* nextNode() const { return this->next; }
	Node<T, T1>* prevNode() const { return this->prev; }

	void insertAfter(Node<T, T1>* obj);
	void insertBefore(Node<T, T1>* obj);
	Node<T, T1>* deleteNode();

};

template<class T, class T1>
void Node<T, T1>::insertAfter(Node<T, T1>* obj) {
	if (this->next != NODE_NULL) {
		obj->next = this->next;
		this->next->prev = obj;
		obj->prev = this;
		this->next = obj;
	}
	else {
		this->next = obj;
		obj->prev = this;
	}
}

template<class T, class T1>
Node<T, T1>* Node<T, T1>::deleteNode() {

	this->prev->next = this->next;
	this->next->prev = this->prev;
	return this;

}

template<class T, class T1>
void Node<T, T1>::insertBefore(Node<T, T1>* obj) {
	if (this->prev != NODE_NULL) {
		obj->prev = this->prev;
		this->prev->next = obj;
		obj->next = this;
		this->prev = obj;
	}
	else {
		this->prev = obj;
		obj->next = this;
	}
}
