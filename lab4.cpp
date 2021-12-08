#include <iostream>
#include <bitset>
#include <set>
using namespace std;

template<size_t N>
class Bitset {

private:

	

public:

	class reference {

		friend class Bitset<N>;

	private:

		Bitset<N>* _Bitset;
		size_t curPos;

	public:



	};

	bool field[N];
	Bitset(unsigned long long value) {

		construct(value);
		//bool bit;
		bool* begin = field;
		bool* end = field + sizeof(field) / sizeof(*field) - 1;

		while (begin < end) {
			*begin ^= *end ^= *begin ^= *end;
			begin++; end--;
		}

		

	}

	void construct(unsigned long long value) {

		int s = 0x1;
		for (size_t index = 0; index < N; index++) {

			field[index] = value & s;
			s <<= 1;
			//field[index] = value & s;

		}

	}

	size_t number() {

		size_t byte = 0;
		for (size_t index = 0; index < N; index++) {

			byte = (byte << 1) | field[index];

		}
		return byte;
	}

	Bitset& operator&=(const Bitset& obj) {

		for (size_t index = 0; index < N; index++) {

			field[index] &= obj.field[index];

		}

		return *this;

	}


};

int main() {

	Bitset<32> e(1435);
	Bitset<32> a(1337);
	for (int i = 0; i < 32; i++) {
		cout << e.field[i];
	}
	cout << endl;
	bitset<32> yeye(1435);
	bitset<32> eeee(1337);
	cout << yeye << endl;

	
	yeye &= eeee;
	cout << yeye << endl;
	e &= a;
	for (int i = 0; i < 32; i++) {
		cout << e.field[i];
	}
	cout << endl;

	return 0;
}
