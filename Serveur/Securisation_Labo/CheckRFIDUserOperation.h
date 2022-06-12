#pragma once
#include "Operation.h"

#include <qstring.h>
#include <qthread.h>

class CheckRFIDUserOperation : public Operation
{
	QString idCard;
	bool accessAuthorized;

public:
	/* Constructor CheckRFIDUserOperation class */
	CheckRFIDUserOperation(QString idCard);

	/* Run CheckRFIDUserOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

class LockOpeningThread : public QThread
{
public:
	/* Run LockOpeningThread thread */
	virtual void run() override;
};