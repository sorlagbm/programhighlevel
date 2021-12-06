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
            this->work = work;

        }

    };
    vector<User> _queue;

public:

    struct FileWork{

        QFile* file;
        QString fileName;
        bool isChanged;

        FileWork(QFile* _file = nullptr, QString _fileName = "")
            :file(_file), fileName(_fileName)
        {}
        FileWork(const FileWork& copy){

            this->file = copy.file;
            this->fileName = copy.fileName;
            this->isChanged = false;

        }

    }*curFile;
    QTableWidget* curWid;
    size_t q_rows;

    Queue(int i = 0, FileWork* _curFile = nullptr, QTableWidget* _curWid = nullptr, size_t _q_rows = 0);

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
