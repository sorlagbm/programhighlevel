#include <iostream>
#include <string>
using namespace std;
//22

class student_list {

private:
	struct student {

		string fio;
		unsigned group_n;
		unsigned m_mark;
		student() {
			
			this->fio = "";
			this->group_n = 0;
			this->m_mark = 0;

		}

	};
	unsigned n;
	student* _student = new student();
	student_list* list;

public:
	student_list(): n(0) { list = new student_list[this->n]; }
	student_list(unsigned n) {

		this->n = n;
		list = new student_list[this->n];

	}
	string& rfio() const { return this->_student->fio; }
	unsigned& rgroup_n() const { return this->_student->group_n; }
	unsigned& rm_mark() const { return this->_student->m_mark; }
	student_list r_el(int i) const{

		cout << "Номер: " << i << " " << "ФИО:" << this->_student->fio
			<< "Номер группы: " << this->_student->group_n << " "
			<< "Средняя оценка:" << this->_student->m_mark << "\n";
		return *this;
		 
	}
	friend ostream& operator<<(ostream& file, const student_list& obj) {

		file << "ФИО:" << obj._student->fio
			<< "Номер группы: " << obj._student->group_n << " "
			<< "Средняя оценка:" << obj._student->m_mark << "\n";
		return file;

	}
	student_list operator!() {

		for (int i = 0; i < this->n; i++) {

			list[i]._student->fio = "";
			list[i]._student->group_n = 0;
			list[i]._student->m_mark = 0;

		}
		return *this;

	}
	~student_list() {

		if (this->n == 0) delete list;
		else delete[] list;
		delete _student;

 	}

};

int operator++(student_list& e) {

	e.rgroup_n()++;
	return e.rgroup_n();

}

int main() {

		

	return 0;

}
