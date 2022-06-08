#pragma once

#include "database.h"

#include <qdatetime.h>
#include <qdebug.h>

class timeSlot
{

/* Define time */
#define coursStartTime		"06:00:00"
#define coursEndTime		"23:00:00"

public:

	timeSlot(database * db);
	~timeSlot();

	static timeSlot * getInstance(database * db);

	static bool validateTime();
	static void initTimeSlot();
	static void changeRegularTime();

private:

	static QString startTime;
	static QString endTime;
	static QString access;

	static timeSlot * instance;

	database * db;

};

