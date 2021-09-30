#include <iostream>
#include <string>
using namespace std;
//17

//Перечисляемый тип
enum Status {

    off,
    on,
    avia,
    charge,
    no_charge

};

class MobileOS {

private:
    float wifi_ghz;
    short battery_capacity;
    bool isNfc;
    string model_name;
    // Поле этого перечисляемого типа
    Status status;

public:
    MobileOS();
    MobileOS(float wifi_ghz, short battery_capacity, bool isNfc, string model_name, Status status);
    MobileOS(const MobileOS& device);
    ~MobileOS();

};

MobileOS::MobileOS() : wifi_ghz(0.0), battery_capacity(0),
isNfc(false), model_name("no_name"), status(off) {

    cout << "object has been created with a standart parameters" << "\n"
        << "WiFi: " << this->wifi_ghz << "GHz" << "\n"
        << "Battery Capacity: " << this->battery_capacity << "mAh" << "\n"
        << "Nfc: " << this->isNfc << "\n"
        << "Model Name: " << this->model_name << "\n"
        << "Status: " << this->status << "\n";

}

MobileOS::MobileOS(float wifi_ghz, short battery_capacity,
    bool isNfc, string model_name, Status status) {

    this->wifi_ghz = wifi_ghz;
    this->battery_capacity = battery_capacity;
    this->isNfc = isNfc;
    this->model_name = model_name;
    this->status = status;

    cout << "object has been created with:" << "\n"
        << "WiFi: " << this->wifi_ghz << "GHz" << "\n"
        << "Battery Capacity: " << this->battery_capacity << "mAh" << "\n"
        << "Nfc: " << this->isNfc << "\n"
        << "Model Name: " << this->model_name << "\n"
        << "Status: " << this->status << "\n";

}

MobileOS::MobileOS(const MobileOS& device) {

    this->wifi_ghz = device.wifi_ghz;
    this->battery_capacity = device.battery_capacity;
    this->isNfc = device.isNfc;
    this->model_name = device.model_name;
    this->status = device.status;

    cout << "object has been created with another device's parameters:" << "\n"
        << "WiFi: " << this->wifi_ghz << "GHz" << "\n"
        << "Battery Capacity: " << this->battery_capacity << "mAh" << "\n"
        << "Nfc: " << this->isNfc << "\n"
        << "Model Name: " << this->model_name << "\n"
        << "Status: " << this->status << "\n";

}

MobileOS::~MobileOS() {

    cout << "object has been deleted with:" << "\n"
        << "WiFi: " << this->wifi_ghz << "GHz" << "\n"
        << "Battery Capacity: " << this->battery_capacity << "mAh" << "\n"
        << "Nfc: " << this->isNfc << "\n"
        << "Model Name: " << this->model_name << "\n"
        << "Status: " << this->status << "\n";

}

//Функция для перевода числа в перечисляемый тип Status(сделана потому, что нельзя просто присвоить число другому перечисляемому типу)
Status from_int_to_status(int n) {

    if (n == 0) return off;
    if (n == 1) return on;
    if (n == 2) return avia;
    if (n == 3) return charge;
    if (n == 4) return no_charge;

}

int main() {

    MobileOS* c = new MobileOS(2.4, 5000, true, ")))0", on);
    MobileOS a[2];
    MobileOS* b = new MobileOS[2];

    for (int i = 0; i < 2; i++) {

        float wifi_ghz;
        short battery_capacity;
        bool isNfc;
        string model_name;
        Status status;
        int s;
        cin >> wifi_ghz >> battery_capacity >> isNfc >> s;

        b[i] = MobileOS(wifi_ghz, battery_capacity, isNfc, "gafo", from_int_to_status(s));

    }

    for (int i = 0; i < 2; i++) {

        //b[i] = MobileOS(2.2, 423, true, "gafo", avia);
        b[i].~MobileOS();

    }

    delete c;

}
