#include <iostream>
#include <bitset>
#include <set>
#include <fstream>
using namespace std;

template<size_t N>
class Bitset {

private:

	size_t size;

public:

	class reference {

		friend class Bitset<N>;

	private:

		Bitset<N>* _Bitset;
		size_t curPos;

	public:



	};

	bool field[N];
	size_t get_size() const { return this->size; }
	Bitset(unsigned long long value) {

		construct(value);
		//bool bit;
		bool* begin = field;
		bool* end = field + sizeof(field) / sizeof(*field) - 1;

		while (begin < end) {
			*begin ^= *end ^= *begin ^= *end;
			begin++; end--;
		}
		size = N;

	}

	void construct(unsigned long long value) {

		int s = 0x1;
		for (size_t index = 0; index < N; index++) {

			field[index] = value & s;
			s <<= 1;
			//field[index] = value & s;

		}

	}

	bool& operator[](int i) {
		return field[size - 1 - i];
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

	Bitset& operator|=(const Bitset& obj) {

		for (size_t index = 0; index < N; index++) {

			field[index] |= obj.field[index];

		}

		return *this;

	}

	Bitset& operator<<=(size_t pos) {

		int e = number();
		e <<= pos;
		Bitset<N> copy(e);
		for (size_t index = 0; index < N; index++) {

			field[index] = copy.field[index];

		}
		return *this;

	}

	Bitset& operator>>=(size_t pos) {

		int e = number();
		e >>= pos;
		Bitset<N> copy(e);
		for (size_t index = 0; index < N; index++) {

			field[index] = copy.field[index];

		}
		return *this;

	}

	friend ostream& operator<<(ostream& exit, const Bitset<N>& obj) {

		for (int i = 0; i < 32; i++) {
			exit << obj.field[i];
		}
		return exit;

	}

};

int main() {

	Bitset<32> e(1435);
	Bitset<32> a(1337);
	cout << e << endl;
	bitset<32> yeye(1435);
	bitset<32> eeee(1337);
	cout << yeye << endl;

	yeye &= eeee;
	cout << yeye << endl;
	e &= a;
	cout << e << endl;

	yeye |= eeee;
	cout << yeye << endl;
	e |= a;
	cout << e << endl;

	yeye <<= 5;
	cout << yeye << endl;
	e <<= 5;
	cout << e << endl;

	yeye >>= 5;
	cout << yeye << endl;
	e >>= 5;
	cout << e << endl;

	cout << yeye[0] << endl;
	cout << e[0] << endl;

	return 0;
}
