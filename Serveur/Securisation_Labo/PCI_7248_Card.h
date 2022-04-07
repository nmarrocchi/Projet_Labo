#pragma once
#include "Dask.h"

class PCI_7248_Card
{

public:

	PCI_7248_Card() {
		DIO_PortConfig(this->card, Channel_P1A, INPUT_PORT);
	}

	bool readCard(U16 channel, U16 sensor);

	void writeCard(U16 channel, U16 sensor, U16 value);

private:

	U16 card = Register_Card(PCI_7248, 0);

	int channel;

	int sensor;

	unsigned short value;

};

