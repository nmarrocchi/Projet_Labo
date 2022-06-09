#pragma once
#include "security.h"
#include "Operation.h"

class SensorStateChangedOperation : public Operation
{
	security * sensor;
	bool sensorState;
	int sensorStateI;

public:
	SensorStateChangedOperation(security * sensor, bool sensorState, int sensorStateI);

	virtual void run();
	virtual void onOperationDone();
};

