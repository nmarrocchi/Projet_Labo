#include "SystemData.h"

SystemData::SystemData()
{
}

void SystemData::setData(QList<bool> continuityStates, QList<bool> sensorStates, QList<bool> tamperStates, QList<bool> presenceStates)
{
	this->continuityStates	= continuityStates;
	this->sensorStates		= sensorStates;
	this->tamperStates		= tamperStates;
	this->presenceStates	= presenceStates;
}
