#pragma once

#include "database.h"

#include <qdatetime.h>
#include <qdebug.h>

class timeSlot
{

/* Define time */
#define coursStartTime		"06:00:00"
#define coursEndTime		"22:30:00"

public:

	/* Constructor */
	timeSlot(database * db);

	/* Destructor */
	~timeSlot();

	/* Create timeSlot instance */
	static timeSlot * getInstance(database * db);

	/* Validate the actual time slot */
	static bool validateTime();

	/* Initialisation time slot */
	static void initTimeSlot();

	/* Update the datetime automatic in database  */
	static void changeRegularTime();

private:

	static QString startTime;
	static QString endTime;
	static QString access;

	/* Set securitySystem Instance to NULL */
	static timeSlot * instance;

	database * db;

};

