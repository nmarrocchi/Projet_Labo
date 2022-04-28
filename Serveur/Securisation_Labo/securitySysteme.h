#pragma once

#include <qthread.h>
#include <qlist.h>

#include "security.h"

class securitySysteme : public QThread
{
	Q_OBJECT

private:
	static securitySysteme * instance;
	securitySysteme();
	QList<security*> secDevices;
	database * db;

protected:

	virtual void run() override;

public:
	
	static securitySysteme * getInstance();

};

