#pragma once

#include "database.h"

#include <qdatetime.h>
#include <qdebug.h>

class timeSlot
{
public:

	static bool validateTime(database * db);
	static void changeRegularTime(database * db);

private:

	static QString startTime;
	static QString endTime;

	database * db;
};

