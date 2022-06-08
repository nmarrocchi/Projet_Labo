#include "timeSlot.h"

QString timeSlot::startTime = NULL;
QString timeSlot::endTime	= NULL;
QString timeSlot::access	= NULL;

// - Set securitySystem Instance to NULL
timeSlot * timeSlot::instance = NULL;

timeSlot * timeSlot::getInstance(database * db)
{
	if (instance == NULL)
	{
		new timeSlot(db);
	}

	return instance;
}

timeSlot::timeSlot(database * db)
{
	this->db = db;

	initTimeSlot();
}

timeSlot::~timeSlot()
{
}

bool timeSlot::validateTime()
{
	QString timeNow = QDateTime::currentDateTime().toString("hh:mm:ss");

	QSqlQuery query;
	query.exec("SELECT `startTime`, `endTime`, `access` FROM `timeSlot` WHERE active = 1");

	if (query.next())
	{
		timeSlot::startTime = query.value(0).toString();
		timeSlot::endTime	= query.value(1).toString();
		timeSlot::access	= query.value(2).toString();

		if (timeNow < startTime && timeNow > endTime)
		{
			return false;
		}
		else {
			if (access == "0")
			{
				return false;
			}
			else {
				return true;
			}
		}
	}

	return false;
}

void timeSlot::initTimeSlot()
{
	QSqlQuery query;
	query.exec("SELECT `name` FROM `timeSlot` WHERE active = 1");
	if (query.next())
	{
		QString name	= query.value(0).toString();
		QString dayNow	= QDateTime::currentDateTime().toString("dddd");

		if (name == "Cours")
		{
			if (dayNow != "samedi" || dayNow != "dimanche")
			{
				QString dateNow = QDateTime::currentDateTime().toString("yyyy-MM-dd");

				query.exec("UPDATE `timeSlot` SET `startTime`='" + dateNow + " " + coursStartTime + "',`endTime`='" + dateNow + " " + coursStartTime + "' WHERE `name`= '" + name + "'");
			}
		}
	}
}

void timeSlot::changeRegularTime()
{
	QSqlQuery query;
	query.exec("SELECT `name` FROM `timeSlot` WHERE active = 1");
	if (query.next())
	{
		QString name = query.value(0).toString();

		if (name == "Cours")
		{
			QString dayNow	= QDateTime::currentDateTime().toString("dddd");
			QString timeNow = QDateTime::currentDateTime().toString("hh:mm:ss");
			
			if (dayNow != "samedi" || dayNow != "dimanche")
			{
				if (timeNow > "00:00:00" || timeNow < "00:00:01")
				{
					QString dateNow = QDateTime::currentDateTime().toString("yyyy-MM-dd");

					query.exec("UPDATE `timeSlot` SET `startTime`='" + dateNow + " " + coursStartTime + "',`endTime`='" + dateNow + " " + coursEndTime + "' WHERE `name`= '" + name + "'");
				}
			}
		}
	}
}
