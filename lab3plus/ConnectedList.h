#pragma once
#include "Node.h"

class ConnectedList {
	/*
	Node<int>* head = new Node<int>(15);
	Node<int>* cur = new Node<int>(54, head);
	cout << cur->getData() << endl;
	cur = cur->nextNode();
	cout << cur->getData() << endl;
	cur->insertAfter(new Node<int>(345));
	cur = cur->nextNode();
	cout << cur->getData() << endl;
	cur = cur->prevNode();
	cout << cur->getData() << endl;

	cout << endl;

	Node<int>* a = new Node<int>(4);
	cout << a->getData() << endl;
	a->insertAfter(new Node<int>(23423));
	a = a->nextNode();
	cout << a->getData() << endl;
	*/

private:
	Node *head, *tail, *cur;

	size_t lenght;
	size_t pos;

public:
	ConnectedList(Money value_of_head = Money(), Date second_of_head = Date())
		: head(new Node(value_of_head, second_of_head)), cur(head), tail(head)
		,lenght(0), pos(0) {}

	void _next() {
		if (cur != NODE_NULL && cur->nextNode() != NODE_NULL) {
			cur = cur->nextNode();
			pos += 1;
		}
	}
	void _prev() {
		if (cur != NODE_NULL && cur->prevNode() != NODE_NULL) {
			cur = cur->nextNode();
			pos -= 1;
		}
	}

	size_t size() const { return lenght; }
	size_t curPos() const { return pos; }
	Money& dataFirst() { return cur->getFirst(); }
	Date& dataSecond() { return cur->getSecond(); }

	bool isEnd() const {
		return cur == tail ? true : false;
	}

	void insertAfter(Node* item);
	void deleteNode(int n);

	void reset(int pos = 0);

};

void ConnectedList::insertAfter(Node* item) {
	tail->insertAfter(item);
	lenght += 1;
}

void ConnectedList::deleteNode(int n) {
	cur = head->nextNode();
	for (int j = 1; j != n; j++)
		cur = cur->nextNode();
	cur->deleteNode();
}

void ConnectedList::reset(int pos) {
	if (pos == 0) {
		cur = head;
		tail = head;
		this->pos = 0;
	}
	else {
		cur = head->nextNode();
		this->pos = 1;
		for (; this->pos != pos; this->pos++) {
			cur = cur->nextNode();
		}
	}
}
