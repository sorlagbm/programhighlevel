#include <iostream>
#include <vector>
using namespace std;

int del_count(int n) {

    size_t result = 0;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0) // если остаток от деления = 0, это значит, что число i - делитель
        {
            result++;
        }
    }

    return result;
}

int main(){

    int n, k;
    cin >> n >> k;

    vector<int> a(n, 5);
    vector<int> result;

    for (int i = 0; i < a.size(); i++)
    {
        if(del_count(a[i]) >= k)
        a.insert(a.begin() + i + 1, 0);
        i++;
    }

    for (auto&& e : a) {
        cout << e << " ";
    }

    return 0;
}
