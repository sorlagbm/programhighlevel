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
    us n;

public:
    journal() : n(0) { list = vector<student>(this->n); }
    explicit journal(us n) { this->n = n; list = vector<student>(this->n);}
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

        this->n = obj.n;
        this->list.clear();
        this->list.resize(this->n);
        for (int i = 0; i < this->n; i++) {

            this->list[i].fio = obj.list[i].fio;
            this->list[i].gn = obj.list[i].gn;
            this->list[i].m = obj.list[i].m;

        }
        return *this;

    }
    friend ostream& operator<<(ostream& file, const journal& obj) {

        for (int i = 0; i < obj.n; i++) {

            file << "N:" << i << " "
                << "FIO:" << obj.list[i].fio << " "
                << "Group Number:" << obj.list[i].gn << " "
                << "Mark:" << obj.list[i].m << "\n";

        }
        return file;

    }
    void set_list(us i, string fio, us gn, us m) {this->list[i] = student(fio, gn, m); }
    //void sort_list() { sort(this->list.begin(), this->list.end()); }
    ~journal() { list.~vector(); }

};

int main() {

    int c;
    cin >> c;
    journal j(c);
    for (int i = 0; i < c; i++) {

        cin >> j.get_fio(i);
        cin >> j.get_gn(i);
        cin >> j.get_m(i);

    }
    cout << j << "\n";
    j[0];

    return 0;

}
