#include "SystemData.h"

SystemData::SystemData()
{
}

void SystemData::setData(QList<bool> tamperStates, QList<bool> continuityStates, QList<bool> presenceStates, QList<bool> sensorStates)
{
	this->tamperStates = tamperStates;
	this->continuityStates = continuityStates;
	this->presenceStates = presenceStates;
	this->sensorStates = sensorStates;
}
