#pragma once
#include "Operation.h"
#include <qwebsocket.h>

class SendAuthResultOperation :
	public Operation
{
	QWebSocket * ws;
	int result;

public:
	SendAuthResultOperation(QWebSocket * ws, int result);
	virtual void run();
	virtual void onOperationDone();
};

