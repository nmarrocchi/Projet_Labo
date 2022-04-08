#pragma once
#include "Dask.h"

class PCI_7248_Card
{

public:

	PCI_7248_Card() {
		card = Register_Card(PCI_7248, 0);
		for (int i = 0; i < 3; i++)
		{
			//DIO_PortConfig(this->card, i, INPUT_PORT);
		}

		for (int i = 5; i < 8; i++)
		{
			//DIO_PortConfig(this->card, i, OUTPUT_PORT);
		}
	}

	bool readCard(U16 channel, U16 sensor);

	void writeCard(U16 channel, U16 sensor, U16 value);

private:

	U16 card;

	int channel;

	int sensor;

	unsigned short value;

};

