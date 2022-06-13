#pragma once
#include "Operation.h"
#include "securitySysteme.h"

class ActiveActuatorOperation : public Operation
{
	int channel;
	int actuator;
	bool value;

public:
	/* Constructor ActiveActuatorOperation class */
	ActiveActuatorOperation(int channel, int actuator, bool value);

	/* Run ActiveActuatorOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

