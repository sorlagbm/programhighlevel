#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//22
class journal {

    using us = unsigned short;

private:
    struct student {

        string fio;
        us gn;
        us m;
        student() {

            this->fio = "";
            this->gn = 0;
            this->m = 0;

        }
        student(string fio, us gn, us m) {

            this->fio = fio;
            this->gn = gn;
            this->m = m;

        }

    };
    vector<student> list;

public:
    journal() { list = vector<student>(0); }
    explicit journal(us n) { list = vector<student>(n);}
    string& get_fio(us c) { return this->list[c].fio; }
    us& get_gn(us c) { return this->list[c].gn; }
    us& get_m(us c) { return this->list[c].m; }
    journal operator[](int i) { 
        
        cout << "FIO:" << this->list[i].fio << " "
            << "Group Number:" << this->list[i].gn << " "
            << "Mark:" << this->list[i].m << "\n";
        return *this;

    }
    journal operator=(const journal& obj) {

        this->list.clear();
        this->list.resize(obj.list.size());
        for (int i = 0; i < this->list.size(); i++) {

            this->list[i].fio = obj.list[i].fio;
            this->list[i].gn = obj.list[i].gn;
            this->list[i].m = obj.list[i].m;

        }
        return *this;

    }
    friend ostream& operator<<(ostream& file, const journal& obj) {

        for (int i = 0; i < obj.list.size(); i++) {

            file << "N:" << i << " "
                << "FIO:" << obj.list[i].fio << " "
                << "Group Number:" << obj.list[i].gn << " "
                << "Mark:" << obj.list[i].m << "\n";

        }
        return file;

    }
    void add(string fio, us gn, us m) {

        student* e = new student(fio, gn, m);
        this->list.push_back(*e);
        delete e;

    }
    void _erase() { this->list.erase(this->list.end() - 1); }
    void set_list(us i, string fio, us gn, us m) {this->list[i] = student(fio, gn, m); }
    void sort_list() { 

        vector<string> t(this->list.size());
        for (int i = 0; i < this->list.size(); i++) {

            t[i] = this->list[i].fio;

        }
        sort(t.begin(), t.end()); 
        for (int i = 0; i < this->list.size(); i++) {

            this->list[i].fio = t[i];

        }

    }
    ~journal() { list.~vector(); }

};

int main() {

    int c;
    cin >> c;
    journal* j = new journal(c);
    for (int i = 0; i < c; i++) {

        cin >> j->get_fio(i);
        cin >> j->get_gn(i);
        cin >> j->get_m(i);

    }
    cout << *j << "\n";
    j[c - 1];
    j->sort_list();
    cout << *j << "\n";
    j->add("new_student", 0, 0);
    cout << *j << "\n";
    j->_erase();
    cout << *j << "\n";
    vector<journal> u(c);
    for (int i = 0; i < c; i++) {

        u[i] = journal(3);

    }
    for (int i = 0; i < c; i++) {

        for (int j = 0; j < 3; j++) {

            u[i].set_list(j, "new_student", 0, 0);

        }

    }
    for (int i = 0; i < c; i++) {

        cout << u[i] << "\n";

    }
    *j = u[0];
    cout << *j << "\n";
    return 0;

}
