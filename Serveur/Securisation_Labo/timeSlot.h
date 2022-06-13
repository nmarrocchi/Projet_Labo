#pragma once

#include "database.h"
#include "ConfigData.h"

#include <qdatetime.h>
#include <qdebug.h>

class timeSlot
{
public:

	/* Constructor */
	timeSlot(QString startTime, QString endTime);

	/* Destructor */
	~timeSlot();

	/* Create timeSlot instance */
	static timeSlot * getInstance(QString startTime, QString endTime);

	/* Validate the actual time slot */
	static bool validateTime();

	/* Initialisation time slot */
	static void initTimeSlot();

	/* Update the datetime automatic in database  */
	static void changeRegularTime();

private:

	static QString access;

	static QString startTime;
	static QString endTime;

	/* Set securitySystem Instance to NULL */
	static timeSlot * instance;

	database * db;

};

