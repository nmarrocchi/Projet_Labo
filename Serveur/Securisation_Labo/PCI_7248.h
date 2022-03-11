#pragma once
class PCI_7248
{

public:

	bool readCard(int channel, int sensor, int value);

	void writeCard(int channel, int sensor, int value);

private:

	//I16 card = Register_Card(PCI_7248, 0);

	int channel;

	int sensor;

	unsigned short value;

};

