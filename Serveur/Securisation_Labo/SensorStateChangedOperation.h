#pragma once
#include "Operation.h"
#include "security.h"
#include "securitySysteme.h"

class SensorStateChangedOperation : public Operation
{
	security * sensor;
	bool sensorState;
	int sensorByte;

public:
	/* Constructor SensorStateChangedOperation class */
	SensorStateChangedOperation(security * sensor, bool sensorState, int sensorByte);

	/* Run SensorStateChangedOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

