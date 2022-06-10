#pragma once
#include "Operation.h"
class ActiveActuatorOperation : public Operation
{
	int channel;
	int actuator;
	bool value;

public:
	ActiveActuatorOperation(int channel, int actuator, bool value);

	virtual void run();
	virtual void onOperationDone();
};

