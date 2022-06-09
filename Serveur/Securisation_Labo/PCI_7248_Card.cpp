#include "PCI_7248_Card.h"

/* Call function in Dask lib to read values on PCI_7248_Card */
bool PCI_7248_Card::readCard(U16 channel, U16 sensor)
{

	DO_ReadLine(card_number, channel, sensor, &value);
	return value;

}

/* Call function in Dask lib to send values on PCI_7248_Card */
void PCI_7248_Card::writeCard(U16 channel, U16 sensor, U16 value)
{

	DO_WriteLine(card_number, channel, sensor, value);

}
