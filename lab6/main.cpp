#include <iostream>
#include <ostream>
#include <string>
#include "ConnectedList.h"
using namespace std;

class EmptyList_exception : public exception {
private:
    string message;
public:
    EmptyList_exception(string error = "") {
        message = error;
    }
    const char* what() const noexcept { return message.c_str(); }
};

template<class T>
class Queue {

public:

    Queue() {
        list = ConnectedList<T>();
    }

    void push_back(const T& item) {
        list.insertAfter(new Node<T>(item));
    }
    void pop() {
        if (list.isEmpty() == true) throw EmptyList_exception();
        else list.pop();
    }

    size_t size() const { return list->lenght; }
    bool isEmpty() const { return list->isEmpty(); }
    void clear() {
        list.clear();
    }

    template< typename T>
    friend ostream& operator<<(ostream& file, Queue<T>& queue);

private:

    ConnectedList<T> list;

};

template<class T>
ostream& operator<<(ostream& file, Queue<T>& queue) {

    queue.list.reset();
    for (int i = 0; i < queue.list.size(); i++) {
        file << queue.list.data() << " ";
        queue.list._next();
    }
    return file;

}

int main(){

    Queue<int> a;
    try {
        a.pop();
    }
    catch (EmptyList_exception& a) {
        cout << "Empty List" << endl;
    }

    for (int i = 0; i < 15; i++) {
        a.push_back(i);
    }

    cout << a << endl;

    a.pop();

    cout << a;
    return 0;
}
