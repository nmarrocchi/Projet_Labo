#pragma once

#include <qthread.h>
#include <qlist.h>

#include "security.h"

class securitySysteme : public QThread
{
	Q_OBJECT

private:
	static securitySysteme * instance;
	securitySysteme(database * db);
	QList<security*> secDevices;
	database * _db;

protected:

	virtual void run() override;

public:
	
	static securitySysteme * getInstance(database * db);

};

