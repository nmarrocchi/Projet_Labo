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

	void setData(QList<bool> tamperStates, QList<bool> continuityStates, QList<bool> presenceStates, QList<bool> sensorStates);

	QList<bool> getTamperStates() { return tamperStates; }
	QList<bool> getContinuityStates() { return continuityStates; }
	QList<bool> getPresenceStates() { return presenceStates; }
	QList<bool> getSensorStates() { return sensorStates; }
};

