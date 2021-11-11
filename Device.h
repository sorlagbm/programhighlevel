#pragma once
#include "CPU.h"
#include "GPU.h"
#include <iostream>
class Device{
	
public:

	unsigned id;
	virtual void get_information() = 0;
	unsigned get_guid() {
		return this->id;
	};
	Device() {
		std::cout << "DEvice created" << "\n";
	}

};