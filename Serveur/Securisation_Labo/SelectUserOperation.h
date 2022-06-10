#pragma once
#include "Operation.h"
#include <qstring.h>
#include <qwebsocket.h>

class SelectUserOperation : public Operation
{
	QWebSocket * ws;

	QString idCard;
	QString mail;
	QString password;
	QString admin;

	QString result;

public:
	SelectUserOperation(QWebSocket * ws);

	virtual void run();
	virtual void onOperationDone();
};

