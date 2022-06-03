#pragma once

#include <qlist.h>

class SystemData
{
private:
	QList<bool> tamperStates;
	QList<bool> continuityStates;
	QList<bool> presenceStates;
	QList<bool> sensorStates;


public:
	SystemData();

	void setData(QList<bool> continuityStates, QList<bool> sensorStates, QList<bool> tamperStates, QList<bool> presenceStates);

	QList<bool> getContinuityStates() { return continuityStates; }
	QList<bool> getSensorStates() { return sensorStates; }
	QList<bool> getTamperStates() { return tamperStates; }
	QList<bool> getPresenceStates() { return presenceStates; }
};

