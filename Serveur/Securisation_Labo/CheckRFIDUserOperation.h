#pragma once
#include "Operation.h"
#include "webServer.h"

#include <qstring.h>
#include <qthread.h>

class CheckRFIDUserOperation : public Operation
{
	webServer * webserver;

	QString idCard;
	QString mailValue;
	QString dateValue;

	bool accessAuthorized;

public:
	/* Constructor CheckRFIDUserOperation class */
	CheckRFIDUserOperation(QString idCard);

	/* Run CheckRFIDUserOperation thread */
	virtual void run();

	/* Update values on historical on client */
	void actualiseHisto();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

class LockOpeningThread : public QThread
{
public:
	/* Run LockOpeningThread thread */
	virtual void run() override;
};