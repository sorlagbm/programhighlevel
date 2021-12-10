#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

int ca(int a) {

    int result = 0;
    while (a != 0) {

        result += 1;
        a /= 10;

    }
    return result;

}

int main()
{

    srand(time(NULL));

    multimap<int, int> result;

    vector<int> a;
    vector<int> b;

    for (int i = 0; i < 16; ++i) {

        a.push_back(0 + rand() % 20);
        b.push_back(0 + rand() % 20);

    }

    for (int i = 0; i < 16; ++i) {

        cout << a[i] << " " << b[i] << endl;

    }
    cout << endl;

    for (int i = 0; i < 16; i++) {

        pair<int, int> e;
        if (a[i] % 10 == b[i] % 10) {
            e.first = a[i];
            e.second = b[i];
        }
        else continue;
        //cout << e.first << " " << e.second << endl;
        result.insert(e);

    }

    for (multimap<int, int>::iterator a = result.begin();
        a != result.end(); ++a) {

        cout << a->first << " " << a->second << endl;

    }

    return 0;
}
