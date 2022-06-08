#include "timeSlot.h"

QString timeSlot::startTime = NULL;
QString timeSlot::endTime = NULL;

bool timeSlot::validateTime(database * db)
{
	QSqlQuery query;
	query.exec("SELECT `startTime`, `endTime` FROM `timeSlot` WHERE active = 1");

	QString timeNow = QDateTime::currentDateTime().toString("hh:mm:ss");

	if (query.next())
	{
		timeSlot::startTime = query.value(0).toString();
		timeSlot::endTime = query.value(1).toString();

		if (timeNow < startTime && timeNow > endTime)
		{
			return false;
		}
		else {
			return true;
		}
	}

	return false;
}


