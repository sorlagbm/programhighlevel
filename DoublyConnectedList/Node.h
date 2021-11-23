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


/* insertAfter's realization
*
* Вставка после текущего элемента  ( I )
*
* 1) 2 ноды связаны между собой.
*	Node_1.next = Node_2; (1)
*
*        Node_1									Node_2
*  --------------------                       --------------------
* | prev | data | Node_2 |	------------->	 | prev | data | next |
*  --------------------					      --------------------
*
* 2) Вставка новой ноды после Node_1
*
* Node_3.next = Node_1.next; // Node_1.next == Node_2    (2)
* Node_1.next = Node_3; // Сделать Node_3 следующей нодой     (3)
*
*        Node_1									Node_2
*  --------------------                       --------------------
* | prev | data | Node_3 |	             	 | prev | data | next |
*  --------------------					      --------------------
*                   |                                    / \
*                   |                Node_3               |
*                   |       ----------------------        |
*                    ----> | prev | data | Node_2 | ------
*                           ----------------------
*
* ( II )
* В случае, если текущая нода - единственная в списке, просто добавить следующую,
* изменив указатель next;
*
*/

/*
*
* deleteAfter's realization
*
* 1) Связаны последовательно 3 ноды
*        Node_1									Node_2
*  --------------------                       --------------------
* | prev | data | Node_3 |	             	 | prev | data | next |
*  --------------------					      --------------------
*                   |                                    / \
*                   |                Node_3               |
*                   |       ----------------------        |
*                    ----> | prev | data | Node_2 | ------
*                           ----------------------
*
* Чтобы удалит элемент, идущий после текущего, нужно:
*  1) Завести промежуточную переменную, в которую записать адрес удаляемого узла
*  2) Текущему next присвоить next удаляемого узла, что будет означать
*		новую связь между элементами
*
*  Node<T>* temp = Node_1.next; // Node_1.next == Node_3 - запись удаляемого узла Node_3
*  Node_1.next = temp.next;     // temp.next == Node_2 - связь Node_1 и Node_2
*  return temp;     // Можно вернуть результат (например, чтобы в будущем освободить
*				    // указатель на удаленный элемент). Можно обойтись без этого
*
*         Node_1									Node_2
*  --------------------                       --------------------
* | prev | data | Node_2 | ----------------> | prev | data | next |
*  --------------------					      --------------------
*                   |                                    / \
*                   -                                     |
*                   -                Node_3               |
					|        ----------------------       |
*                    ----> | prev | data | next | --| |--
*                           ----------------------
*
*  Также обязательна проверка на пустоту Node_1.next для того, чтобы определить,
*  есть ли вообще элемент для удаления
*
*/

/*
*
*  Аналогичным образом должна быть построена работа с insertBefore и deleteBefore,
*  только задействован должен быть указатель prev.
*
*/

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
