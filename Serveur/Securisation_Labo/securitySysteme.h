#pragma once

#include <qthread.h>
#include <qlist.h>

#include "security.h"

class securitySysteme : public QThread
{
	Q_OBJECT

private:
	static securitySysteme * instance;

	// - Instance All Sensors Class
	securitySysteme(database * db);

	QList<security*> secDevices;

protected:
	// - Run securitySystem loop
	virtual void run() override;

public:
	// - Create securitySystem Instance
	static securitySysteme * getInstance(database * db);

};

