#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

template<class T>
class Element {

public:

    //~Element() { data = 0; }
    Element() : data{} {
        is2 = data % 2 == 0 ? true : false;
    }
    Element(const T& value) : data(value) {
        is2 = data % 2 == 0 ? true : false;
    }

    T& value() { return data; }

    bool operator==(const Element<T>& _Element) { return is2 == _Element.is2 ? true : false; }
    Element<T> operator=(const int& _Operand) { data = _Operand; return data; }
    //Element<T>& operator=(const Element<T>& _Operand) { data = _Operand.data; return data; }
    bool operator%(const int& _Operand) { data %= _Operand; return data; }
    operator int() { return data; }
    bool is2;

private:

    T data;

};

int main() {

    vector<Element<int>> vec(8);
    deque<Element<int>> deq(6);

    vec[0] = Element<int>(11); // 0 1 0 1 0 0 1 1
    vec[1] = Element<int>(14); // 0 1 0
    vec[2] = Element<int>(15);
    vec[3] = Element<int>(16);
    vec[4] = Element<int>(17);
    vec[5] = Element<int>(17);
    vec[6] = Element<int>(18);
    vec[7] = Element<int>(10);

    deq[0] = Element<int>(1);
    deq[1] = Element<int>(2);
    deq[2] = Element<int>(3);
    deq[3] = Element<int>(4);
    deq[4] = Element<int>(5);
    deq[5] = Element<int>(6);

    deq.erase(deq.begin() + deq.size() / 2, deq.end());
    cout << deq[2] << endl;

    auto a = search(vec.rbegin(), vec.rend(), deq.rbegin(), deq.rend());

    vec.erase(prev(next(a).base(), 2), next(a).base());

    for (auto i : vec)
        cout << i << " ";

    return 0;
}
