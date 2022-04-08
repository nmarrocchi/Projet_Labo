#include "PCI_7248_Card.h"

bool PCI_7248_Card::readCard(U16 channel, U16 sensor)
{

	DO_ReadLine(this->card, channel, sensor, &value);
	return value;

}

void PCI_7248_Card::writeCard(U16 channel, U16 sensor, U16 value)
{

	DO_WriteLine(this->card, channel, sensor, value);

}
