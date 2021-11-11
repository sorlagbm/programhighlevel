#pragma once
#include "Device.h"
#include "Screen.h"
#include <iostream>
class Computer : public Device{

private:
	virtual void get_information() override {
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
			<< "GUID: " << this->get_guid() << "\n";
	}
public:
	CPU* cpu;
	GPU* gpu;
	Screen* screen;
	Computer(CPU* cpu = nullptr, GPU* gpu = nullptr, unsigned id = 0) {
		this->cpu = cpu;
		this->gpu = gpu;
		this->screen = new Screen(1024, 640);
		this->id = id;
	}
	void get_inf() {
		this->get_information();
	}

};

