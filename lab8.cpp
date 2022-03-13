#include <iostream>
#include <set>
using namespace std;

int main() {

	size_t size;
	cin >> size;

	set<pair<int, int>> graph;

	for (size_t i = 0; i < size; i++) {
		int from, to;
		cin >> from >> to;
		from--; to--;
		graph.insert(pair<int, int>(from, to));
	}
	
	for (set<pair<int, int>>::iterator it = graph.begin(); it != graph.end(); ++it) {
		cout << '[' << it->first + 1 << ' ' << it->second + 1 << "] ";
	}
	cout << endl;
	
	set<pair<int, int>> graph2;

	size_t size2;
	cin >> size2;
	for (size_t i = 0; i < size2; i++) {
		int from, to;
		cin >> from >> to;
		from--; to--;
		graph2.insert(pair<int, int>(from, to));
	}

	for (set<pair<int, int>>::iterator it = graph2.begin(); it != graph2.end(); ++it) {
		cout << '[' << it->first + 1 << ' ' << it->second + 1 << "] ";
	}
	cout << endl;

	for (set<pair<int, int>>::iterator it = graph2.begin(); it != graph2.end(); ++it) {
		graph.insert(*it);
	}

	for (set<pair<int, int>>::iterator it = graph.begin(); it != graph.end(); ++it) {
		cout << '[' << it->first + 1 << ' ' << it->second + 1 << "] ";
	}
	cout << endl;

	return 0;
}
