template <class T>
class Node {
#define NODE_NULL static_cast<Node<T>*>(nullptr)
private:

	Node<T>* prev;
	Node<T>* next;
	T data;

public:

	~Node() { delete next; }
	Node() : data{}, next(NODE_NULL),
		prev(NODE_NULL) {}
	explicit Node(const T& data, Node<T>* _nextNode = NODE_NULL,
		Node<T>* _prevNode = NODE_NULL) {
		this->data = data;
		this->next = _nextNode;
		this->prev = _prevNode;
	}

	T& getData() { return this->data; }
	Node<T>* nextNode() const { return this->next; }
	Node<T>* prevNode() const { return this->prev; }

	void insertAfter(Node<T>* obj);
	Node<T>* deleteAfter(Node<T>* obj);
	void insertBefore(Node<T>* obj);
	Node<T>* deleteBerofe(Node<T>* obj);

};



template<class T>
void Node<T>::insertAfter(Node<T>* obj) {
	if (this->next != NODE_NULL) { // ( I )
		obj->next = this->next; // (2)
		this->next = obj; // (3)
	}
	else { // ( II )
		this->next = obj;
	}
}

template<class T>
Node<T>* Node<T>::deleteAfter(Node<T>* obj) {
	Node<T>* temp = this->next;
	if (this->next == NODE_NULL)
		return NODE_NULL;
	else {
		this->next = temp->next;
		return temp;
	}
}

template<class T>
void Node<T>::insertBefore(Node<T>* obj) {
	if (this->prev != NODE_NULL) {
		obj->prev = this->prev;
		this->prev = obj;
	}
	else { // ( II )
		this->prev = obj;
	}
}

template<class T>
Node<T>* Node<T>::deleteBerofe(Node<T>* obj) {
	Node<T>* temp = this->prev;
	if (this->prev == NODE_NULL)
		return NODE_NULL;
	else {
		this->prev = temp->prev;
		return temp;
	}
}
