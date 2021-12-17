#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
 
class a {

public:

    vector<int> vec;
    deque<int> deq;
    
    size_t step;

    a(int i = 0, int j = 0) {

        vec = vector<int>(i);
        deq = deque<int>(j);

        step = j / 2;

    }

    void construct_e() {

        for (int i = 0; i < deq.size() / 2; i++) {

            if (deq[i] % 2 == 0) e1.push_back(0);
            else e1.push_back(1);

        }

        for (int i = 0; i < 8; i++) {

            if (vec[i] % 2 == 0) vec.push_back(0);
            else vec.push_back(1);

        }

    }

    void swap_halfs() {

        for (int i = 0; i < vec.size() / 2; i++) {

            int t = vec[i];
            vec[i] = vec[vec.size() - i - 1];
            vec[vec.size() - i - 1] = t;

        }

    }

    vector<int> e1;
    vector<int> e2;

};
int main()
{

    a v(8, 6);
    v.vec[0] = 11;
    v.vec[1] = 14;
    v.vec[2] = 15;
    v.vec[3] = 16;
    v.vec[4] = 17;
    v.vec[5] = 17;
    v.vec[6] = 18;
    v.vec[7] = 10;

    v.deq[0] = 1;
    v.deq[1] = 2;
    v.deq[2] = 3;
    v.deq[3] = 4;
    v.deq[4] = 5;
    v.deq[5] = 6;

    v.construct_e();
    
        
    //v.vec.erase(search(v.e1.begin(), next(v.e1.begin(), v.e2.size()), v.e2.begin(), v.e2.end()));

    //reverse(v.vec.begin(), v.vec.end());
    vector<int>::iterator a = prev((find_end(v.vec.begin(), v.vec.end(), v.e1.begin(), v.e1.end())), v.vec.size() / 2);
    v.vec.erase(a, next(a, v.e1.size()));
    //reverse(v.vec.begin(), v.vec.end());
    v.vec.erase(next(v.vec.begin(), v.vec.size() / 2 - 1), v.vec.end());
    for (a = v.vec.begin(); a != v.vec.end(); ++a) {
        cout << *a << " ";
    }
    //cout << *a;
    return 0;
}
