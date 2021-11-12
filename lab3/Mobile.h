#pragma once
#include "Computer.h"
#include "BOS.h"
class Mobile : private Computer, BOS {

private:
	bool isNFC;
	unsigned battery_capacity;
	double wifi_ghz;
	virtual void get_information() override final{

		std::cout << "CPU :" << "\n"
			<< "cores: " << this->cpu->get_cores() << "\n"
			<< "bit: " << this->cpu->get_bit() << "\n"
			<< "Name: " << this->cpu->get_name() << "\n"
			<< "GPU: " << "\n"
			<< "memory: " << this->gpu->get_memory() << "\n"
			<< "Name: " << this->gpu->get_name() << "\n"
			<< "Port: " << this->gpu->get_port() << "\n"
			<< "Screen" << "\n"
			<< "X: " << this->screen->get_x() << "\n"
			<< "Y: " << this->screen->get_y() << "\n"
			<< "GUID: " << this->get_guid() << "\n"
			<< "NFC: " << this->isNFC << "\n"
			<< "Wi-Fi GHZ: " << this->wifi_ghz << "\n"
			<< "OS Name:" << this->name << "\n"
			<< "OS Ver.:" << this->ver << "\n"
			<< "Battery capacity: " << this->battery_capacity << "\n";


	}
public:
	Mobile(CPU* cpu, GPU* gpu, unsigned id, bool isNFC = true, double wifi_ghz = 0.0,
		unsigned battery_capacity = 0, unsigned os_ver = 0, std::string name = " ") {

		this->cpu = cpu;
		this->gpu = gpu;
		this->id = id;
		this->battery_capacity = battery_capacity;
		this->isNFC = isNFC;
		this->ver = os_ver;
		this->wifi_ghz = wifi_ghz;
		this->name = name;
		this->launch_screen();

	}
	void get_inf() {
		this->get_information();
	}
};

