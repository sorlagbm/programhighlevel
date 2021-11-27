#pragma once
#include <string>
#include <cmath>

class Money {

	using dollar = long double;

private:
	dollar value;
public:

	Money() : value(0.0) { }
	Money(const dollar& value) { this->value = value; }
	Money(const Money& _value) { this->value = _value.value; }
	~Money() {}

	dollar& get_value() { return this->value; }

	Money& operator+(const Money& n) { this->value += n.value; }
	Money& operator-(const Money& n) { this->value -= n.value; }
	Money& operator*(dollar& n) { this->value *= n; }
	Money& operator/(dollar& n) { this->value /= n; }
	Money& operator/(const Money& n) { this->value /= n.value; }
	Money& round_value() {

		this->value = std::round(this->value);
		return *this;

	}
	friend long double& operator*(Money& n, long double& val);
	friend long double& operator/(Money& n, long double& val);
	std::string value_to_string() { return std::to_string(this->value); }
	dollar string_to_value(const std::string& value) { return std::stold(value); }

};

long double& operator*(Money& n, long double& val) {

	val *= n.value;
	return val;

}

long double& operator/(Money& n, long double& val) {

	val /= n.value;
	return val;

}

