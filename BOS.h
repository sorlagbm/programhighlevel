#pragma once
#include <iostream>
#include <string>
class BOS{

public:
	unsigned ver;
	std::string name;
public:
	BOS(unsigned ver = 0, std::string name = "") {
		this->ver = ver;
		this->name = name;
	}
	void launch_screen() {
		std::cout << "==================================" << "\n"
			<< "BOS VER.:" << this->ver << "\n"
			<< "==================================" << "\n";
	}

};

