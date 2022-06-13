#pragma once
#include "Operation.h"
#include "webServer.h"

class SendAddHistoOperation : public Operation
{
	webServer * webserver;
	QString result;

public:
	/* Constructor SendAddHistoOperation class */
	SendAddHistoOperation(webServer * webserver, QString result);

	/* Run SendAddHistoOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

