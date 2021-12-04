#ifndef QUEUE_H
#define QUEUE_H
#include <vector>
#include <QString>
#include <QFile>
#include <fstream>
#include <QTableWidget>
using namespace std;

class Queue{
private:
    struct User{

        QString name;
        unsigned denials;
        QString work;
        User(QString name = " ", unsigned denials = 0, QString work = ""){

            this->name = name;
            this->denials = denials;

        }

    };
    vector<User> _queue;

public:
    Queue(int i = 0);
    void _erase(int i){

        _queue.erase(_queue.begin() + i);

    }
    void _resize(int i){
        _queue.resize(i);
    }
    void push(QString name){
        _queue.push_back(User(name));
    }
    void _clear(){
        this->_queue.clear();
    }
    User& operator[](int i){return this->_queue[i];}
    QString& get_name(int i) {return this->_queue[i].name;}
    unsigned get_size() const {return this->_queue.size(); }
    unsigned& get_denials(int i) {return this->_queue[i].denials; }

};

#endif // QUEUE_H
