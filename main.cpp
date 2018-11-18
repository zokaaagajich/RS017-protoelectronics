#include <iostream>
#include <vector>
#include <memory>
#include "components.hpp"
#include "logical_components.hpp"

int main() {
	Resistor *R1 = new Resistor(2000),
			*R2 = new Resistor(3000),
			*R3 = new Resistor(1000),
			*R4 = new Resistor(5000);
	std::vector<Resistor*> r = {R1, R2, R3, R4};

	ParallelConnection *P1 = new ParallelConnection(r[0], r[1]);
	ParallelConnection *P2 = new ParallelConnection(r[2], r[3]);
	SerialConnection *S1 = new SerialConnection(P1, P2);

	DCVoltage U(S1, 10);


	//simple test
	std::cout << "U: " << U.voltage() << std::endl;
	std::cout << "I: " << U.current() << std::endl;
	std::cout << "----------------------" << std::endl;

	std::cout << "Serial U: " << S1->getVoltage() << std::endl;
	std::cout << "Serial I: " << S1->getCurrent() << std::endl;
	std::cout << "----------------------" << std::endl;

	std::cout << "Parallel 1 U: " << P1->getVoltage() << std::endl;
	std::cout << "Parallel 1 I: " << P1->getCurrent() << std::endl;
	std::cout << "----------------------" << std::endl;

	std::cout << "Parallel 2 U: " << P2->getVoltage() << std::endl;
	std::cout << "Parallel 2 I: " << P2->getCurrent() << std::endl;
	std::cout << "----------------------" << std::endl;

	int counter = 1;
	for (auto elem : r) {
		std::cout << "R" << counter << ": " << elem->resistance() << " Ohm" << std::endl;
		std::cout << "Ur" << counter << ": " << elem->getVoltage() << " V" << std::endl;
		std::cout << "I" << counter << ": "<< elem->getCurrent() << " A" << std::endl;
		std::cout << "P" << counter++ << ": "<< elem->power() << " W" << std::endl;
		std::cout << "----------------------" << std::endl;
	}

    double in_1 = 5.0;
    double in_2 = 1;
    std::shared_ptr<InputComponent> in1 =  std::make_shared<InputComponent>(in_1);
    std::shared_ptr<InputComponent> in2 =  std::make_shared<InputComponent>(in_2);
    std::shared_ptr<ANDComponent> and1  = std::make_shared<ANDComponent>(in1, in2); 
    std::shared_ptr<ORComponent> or1 = std::make_shared<ORComponent>(and1,in1);
    XORComponent xor1 = XORComponent(or1, in1);
    NXORComponent nxor1(std::make_shared<XORComponent>(xor1), 2.0); 
    std::cout << "Result: " << nxor1.voltage() << std::endl;
	return 0;
}
