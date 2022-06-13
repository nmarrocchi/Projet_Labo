#pragma once
#include "Operation.h"
#include "webServer.h"

class SendRFIDUserOperation : public Operation
{
	webServer * webserver;
	QString result;

public:
	/* Constructor SendRFIDUserOperation class */
	SendRFIDUserOperation(webServer * webserver, QString result);

	/* Run SendRFIDUserOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

