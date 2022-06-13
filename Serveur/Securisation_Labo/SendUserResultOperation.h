#pragma once
#include "Operation.h"
#include <qwebsocket.h>

class SendUserResultOperation : public Operation
{
	QWebSocket * ws;
	QString result;

public:
	/* Constructor SendUserResultOperation class */
	SendUserResultOperation(QWebSocket * ws, QString result);

	/* Run SendUserResultOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

