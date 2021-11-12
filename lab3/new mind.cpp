#include <iostream>
#include "CPU.h"
#include "GPU.h"
#include "Mobile.h"
#include "Computer.h"
using namespace std;

int main() {

	CPU* a = new CPU(5, 54, "fasdfasd");
	GPU* b = new GPU(4, "ggdfgs", "bxcvbxcv");
	Computer* g = new Computer(a, b, 123);
	g->get_inf();
	Mobile* c = new Mobile(a, b, 14, true, 35, 24, 24, "twertwerb");
	c->get_inf();
	return 0;

}
