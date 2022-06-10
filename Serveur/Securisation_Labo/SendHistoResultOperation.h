#pragma once
#include "Operation.h"
#include <qwebsocket.h>

class SendHistoResultOperation : public Operation
{
	QWebSocket * ws;
	QString result;

public:
	SendHistoResultOperation(QWebSocket * ws, QString result);

	virtual void run();
	virtual void onOperationDone();
};

