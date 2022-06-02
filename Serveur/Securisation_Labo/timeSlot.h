#pragma once

#include "database.h"

#include <qdatetime.h>
#include <qdebug.h>

class timeSlot
{
public:
	static bool validateTime();

private:
	static QString startTime;
	static QString endTime;
};

