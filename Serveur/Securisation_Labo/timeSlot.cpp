#include "timeSlot.h"

QString timeSlot::startTime = NULL;
QString timeSlot::endTime	= NULL;
QString timeSlot::access	= NULL;

/* Set securitySystem Instance to NULL */
timeSlot * timeSlot::instance = NULL;

/* Create timeSlot instance */
timeSlot * timeSlot::getInstance(QString startTime, QString endTime)
{
	if (instance == NULL)
	{
		timeSlot * timeslot = new timeSlot(startTime, endTime);
		instance = timeslot;
	}

	return instance;
}

/* Constructor */
timeSlot::timeSlot(QString startTime, QString endTime)
{
	this->db = db;
	this->startTime = startTime;
	this->endTime = endTime;

	initTimeSlot();
}

/* Destructor */
timeSlot::~timeSlot()
{
}

/* Validate the actual time slot */
bool timeSlot::validateTime()
{
	QString dayNow = QDateTime::currentDateTime().toString("dddd");
	QString timeNow = QDateTime::currentDateTime().toString("hh:mm:ss");

	if (dayNow != "samedi" || dayNow != "dimanche")
	{
		if (timeNow >= startTime && timeNow <= endTime)
		{
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

/* Initialisation time slot */
void timeSlot::initTimeSlot()
{
	/*QSqlQuery query;
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
	}*/
}

/* Update the datetime automatic in database  */
void timeSlot::changeRegularTime()
{
	/*QSqlQuery query;
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
				if (timeNow >= "00:00:00" && timeNow <= "00:00:02")
				{
					QString dateNow = QDateTime::currentDateTime().toString("yyyy-MM-dd");

					query.exec("UPDATE `timeSlot` SET `startTime`='" + dateNow + " " + coursStartTime + "',`endTime`='" + dateNow + " " + coursEndTime + "' WHERE `name`= '" + name + "'");
				}
			}
		}
	}*/
}
