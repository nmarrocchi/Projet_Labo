#include "ActiveActuatorOperation.h"
#include "securitySysteme.h"

ActiveActuatorOperation::ActiveActuatorOperation(int channel, int actuator, bool value) 
	: Operation()
{
	this->channel = channel;
	this->actuator = actuator;
	this->value = value;
}

void ActiveActuatorOperation::run()
{
	securitySysteme::getInstance()->getCard()->writeCard(this->channel, this->actuator, this->value);
}

void ActiveActuatorOperation::onOperationDone()
{
}
