#pragma once
#include "Operation.h"
#include <qwebsocket.h>

class SendHistoResultOperation : public Operation
{
	QWebSocket * ws;
	QString result;

public:
	/* Constructor SendHistoResultOperation class */
	SendHistoResultOperation(QWebSocket * ws, QString result);

	/* Run SendHistoResultOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

