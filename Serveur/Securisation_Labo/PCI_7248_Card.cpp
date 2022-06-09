#include "PCI_7248_Card.h"

/* Call function in Dask lib to read values on PCI_7248_Card */
bool PCI_7248_Card::readCard(U16 channel, U16 sensor)
{
	mutex.lock();
	DO_ReadLine(card_number, channel, sensor, &value);
	mutex.unlock();
	return value;

}

/* Call function in Dask lib to send values on PCI_7248_Card */
void PCI_7248_Card::writeCard(U16 channel, U16 sensor, U16 value)
{
	mutex.lock();
	DO_WriteLine(card_number, channel, sensor, value);
	mutex.unlock();
}
