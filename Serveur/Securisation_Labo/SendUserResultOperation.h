#pragma once
#include "Operation.h"
#include <qwebsocket.h>

class SendUserResultOperation : public Operation
{
	QWebSocket * ws;
	QString result;

public:
	SendUserResultOperation(QWebSocket * ws, QString result);

	virtual void run();
	virtual void onOperationDone();
};

