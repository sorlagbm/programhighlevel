#include <iostream>
using namespace std;

class _time {

private:
    int sec;
    int min;
    int hour;

public:
    _time();//Конструктор по умолчанию I
    _time(int sec, int min, int hour);//Конструктор, инициализирующий секунды, минуты и часы II
    _time(int sec);//Конструктор, который инициализирует минуты и часы на основе поступившего значения секунды III

};

_time::_time() : sec(0), min(0), hour(0) { // I

    cout << this->hour << ":" << this->min << ":" << this->sec << "\n";

}

_time::_time(int sec, int min, int hour) {// II

    if (sec > 59) {

        min += sec / 60;
        sec = 0 + sec % 60;
        if (min > 59) {

            hour += min / 60;
            min = 0 + min % 60;

        }
    }

    this->sec = sec;
    this->min = min;
    this->hour = hour;

    cout << this->hour << ":" << this->min << ":" << this->sec << "\n";

}

_time::_time(int sec) { // III


    hour = sec / 3600;
    min = sec / 60;

    if (sec > 59) {

        min += sec / 60;
        sec = 0 + sec % 60;
        if (min > 59) {

            hour += min / 60;
            min = 0 + min % 60;

        }
    }

    this->sec = sec;
    this->min = min;
    this->hour = hour;

    cout << this->hour << ":" << this->min << ":" << this->sec << "\n";

}

int main() {

    _time clock1 = _time();// 0:0:0
    _time clock2 = _time(144123, 22, 4);//44:24:3
    _time clock3 = _time(1024);//0:34:4

    return 0;

}
 
