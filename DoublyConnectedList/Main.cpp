#include <iostream>
#include "ConnectedList.h"
using namespace std;

template<class T>
class Queue {

public:



private:

    

};

int main(){

    ConnectedList<int> e;
    for (int i = 0; i < 5; i++) {

        e.insertAfter(new Node<int>(i));
        
    }
    cout << e.size() << endl;
    e.reset();
    for (int i = 0; i < e.size(); i++) {

        cout << e.data() << endl;
        e._next();

    }
    cout << endl;
    //e.reset();
    e.pop();
    e.reset();
    for (int i = 0; i < e.size(); i++) {

        cout << e.data() << endl;
        e._next();

    }

    return 0;
}
