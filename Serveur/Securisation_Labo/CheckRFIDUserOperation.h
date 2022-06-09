#pragma once
#include "Operation.h"
#include <qstring.h>
#include <qthread.h>

class LockOpeningThread : public QThread
{
public:
	virtual void run() override;
};

class CheckRFIDUserOperation :
	public Operation
{
	QString idCard;
	bool accessAuthorized;

	virtual void run();
	virtual void onOperationDone();

public:
	CheckRFIDUserOperation(QString idCard);
};

