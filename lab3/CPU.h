#pragma once
#include <string>
class CPU{

private:
	unsigned cores;
	unsigned bit;
	std::string name;
public:
	CPU(unsigned cores = 0, unsigned bit = 0, std::string name = "") {

		this->cores = cores;
		this->bit = bit;
		this->name = name;

	}
	unsigned get_cores() const { return this->cores; }
	unsigned get_bit() const { return this->bit; }
	std::string get_name() const { return this->name; }
};

