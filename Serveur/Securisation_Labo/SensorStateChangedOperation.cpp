#include "SensorStateChangedOperation.h"

/* Constructor SensorStateChangedOperation class */
SensorStateChangedOperation::SensorStateChangedOperation(security * sensor, bool sensorState, int sensorByte)
	: Operation()
{
	this->sensor = sensor;
	this->sensorState = sensorState;
	this->sensorByte = sensorByte;
}

/* Run SensorStateChangedOperation thread */
void SensorStateChangedOperation::run()
{
	// Verification if the time slot is valid
	if (timeSlot::validateTime() == false)
	{
		for (int channel = 5; channel < 8; channel++)
		{
			for (int port = 0; port < 2; port++)
			{
				// Active actuator with PCI_7248_Card class
				securitySysteme::getInstance()->getCard()->writeCard(channel, port, 0);
			}
		}

		// Insert values on historical table in database
		sensor->insertValue(sensorState, sensorByte);

		//mail::sendMail();
	}
}

/* Process when the thread is done */
void SensorStateChangedOperation::onOperationDone()
{
}
