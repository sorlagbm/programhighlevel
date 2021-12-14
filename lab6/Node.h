#pragma once

template <class T>
class Node {
#define NODE_NULL static_cast<Node<T>*>(nullptr)
private:

	Node<T>* prev;
	Node<T>* next;
	T data;

public:

	~Node() {
		delete prev;
		delete next;
	}
	Node() : data{}, next(NODE_NULL),
		prev(NODE_NULL) {}
	explicit Node(const T& data, Node<T>* _nextNode = NODE_NULL,
		Node<T>* _prevNode = NODE_NULL) {
		this->data = data;
		this->next = _nextNode; 
		this->prev = _prevNode;
	}
	Node(const Node<T>*& node) { this = node; }

	T& getData() { return this->data; }
	Node<T>* nextNode() const { return this->next; }
	Node<T>* prevNode() const { return this->prev; }

	void insertAfter(Node<T>* obj);
	void insertBefore(Node<T>* obj);
	Node<T>* deleteNode();

};

template<class T>
void Node<T>::insertAfter(Node<T>* obj) {
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

template<class T>
Node<T>* Node<T>::deleteNode() {

	this->prev->next = this->next;
	this->next->prev = this->prev;
	return this;

}

template<class T>
void Node<T>::insertBefore(Node<T>* obj) {
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

