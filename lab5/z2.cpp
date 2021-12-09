#include <iostream>
#include <set>
using namespace std;

/*
*	1 3 4 6 5 4 - _Set
*	1 3 4 4 5 6 - _Set после ввода (класс сортирует по возрастанию)
*   1 3 - правильный результат
*/

int main() {

	multiset<int> _Set;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {

		int a;
		cin >> a;
		_Set.insert(a);

	}

	int c = 0;

	for (multiset<int>::iterator a = _Set.begin(); a != next(_Set.begin(), n / 2); ++a) {


		for (multiset<int>::iterator b = (next(_Set.begin(), n / 2)); b != _Set.end(); ++b) {
			if (*a != *b) c += 1;
		}
		if (c == n / 2) cout << *a << " ";
		c = 0;


		return 0;
	}
}
