#include "timeSlot.h"

QString timeSlot::startTime = NULL;
QString timeSlot::endTime = NULL;

bool timeSlot::validateTime()
{
	QSqlQuery query;
	query.exec("SELECT `startTime`, `endTime` FROM `timeSlot` WHERE active = 1");

	QString timeNow = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");

	if (query.next())
	{
		timeSlot::startTime = query.value(0).toString();
		timeSlot::endTime = query.value(1).toString();

		if (timeNow < startTime && timeNow > endTime)
		{
			qDebug() << "timeSlot=false " + timeNow;
			//return false;
		}
		else {
			qDebug() << "timeSlot=true " + timeNow;
			//return true;
		}
	}

	return false;
}
