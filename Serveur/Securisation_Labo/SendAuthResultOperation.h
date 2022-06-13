#pragma once
#include "Operation.h"
#include <qwebsocket.h>

class SendAuthResultOperation : public Operation
{
	QWebSocket * ws;
	int result;
	int isAdmin;

public:
	/* Constructor SendAuthResultOperation class */
	SendAuthResultOperation(QWebSocket * ws, int result, int isAdmin);

	/* Run SendAuthResultOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

