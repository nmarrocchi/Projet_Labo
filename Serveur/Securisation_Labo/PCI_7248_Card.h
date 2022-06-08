#pragma once
#include "Dask.h"

class PCI_7248_Card
{

public:

	/* Construct PCI_7248_Card class */
	PCI_7248_Card() {
		card_number = Register_Card(PCI_7248, 0);
		for (int i = 0; i < 3; i++)
		{
			//DIO_PortConfig(this->card, i, INPUT_PORT);
		}

		for (int i = 5; i < 8; i++)
		{
			DIO_PortConfig(this->card_number, i, OUTPUT_PORT);
		}
	}

	/* Call function in Dask lib to read values on PCI_7248_Card */
	bool readCard(U16 channel, U16 sensor);

	/* Call function in Dask lib to send values on PCI_7248_Card */
	void writeCard(U16 channel, U16 sensor, U16 value);

private:

	U16 card_number;

	int channel;

	int sensor;

	unsigned short value;

};

