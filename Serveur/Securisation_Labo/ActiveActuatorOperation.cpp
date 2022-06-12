#include "ActiveActuatorOperation.h"

/* Constructor ActiveActuatorOperation class */
ActiveActuatorOperation::ActiveActuatorOperation(int channel, int actuator, bool value) 
	: Operation()
{
	this->channel = channel;
	this->actuator = actuator;
	this->value = value;
}

/* Run ActiveActuatorOperation thread */
void ActiveActuatorOperation::run()
{
	// Active actuator with PCI_7248_Card class
	securitySysteme::getInstance()->getCard()->writeCard(this->channel, this->actuator, this->value);
}

/* Process when the thread is done */
void ActiveActuatorOperation::onOperationDone()
{
}
