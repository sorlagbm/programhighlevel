#include <iostream> 
#include "ConnectedList.h"
#include "Money.h"
#include "Date.h"
#include <string>
using namespace std;

int main() {
	
	ConnectedList<int> list(256);
	for (int i = 0; i < 5; i++) {
		list.insertAfter(NEW(int, i));
	}
	for (int i = 0; i < 5; i++) {
		cout << list.data() << " ";
		list._next();
	}
	list.deleteNode(2);
	list.reset();
	cout << endl;
	for (int i = 0; i < 4; i++) {
		cout << list.data() << " ";
		list._next();
	}
	return 0;
}
