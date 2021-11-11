#pragma once
class Screen{
private:
	int x;
	int y;
public:
	Screen(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
	int get_x() const { return this->x; }
	int get_y() const { return this->y; }
};

