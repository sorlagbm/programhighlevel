#pragma once
#include <string>
class GPU{

private:
	unsigned memory;
	std::string name;
	std::string port;
public:
	GPU(unsigned memory = 0, std::string name = "", std::string port = "") {

		this->memory = memory;
		this->name = name;
		this->port = port;

	}
	unsigned get_memory() const { return this->memory; }
	std::string get_name() const { return this->name; }
	std::string get_port() const { return this->port; }
};

