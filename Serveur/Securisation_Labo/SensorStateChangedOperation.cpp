#include "SensorStateChangedOperation.h"
#include "securitySysteme.h"

SensorStateChangedOperation::SensorStateChangedOperation(security * sensor, bool sensorState, int sensorStateI)
	: Operation()
{
	this->sensor = sensor;
	this->sensorState = sensorState;
	this->sensorStateI = sensorStateI;
}

void SensorStateChangedOperation::run()
{
	if (timeSlot::validateTime() == false)
	{
		for (int channel = 5; channel < 8; channel++)
		{
			for (int port = 0; port < 2; port++)
			{
				securitySysteme::getInstance()->getCard()->writeCard(channel, port, 0);
			}
		}

		sensor->insertValue(sensorState, sensorStateI);
		//mail::sendMail();
	}
}

void SensorStateChangedOperation::onOperationDone()
{
}
