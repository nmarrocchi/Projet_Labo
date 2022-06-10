#pragma once
#include "Operation.h"
#include <qstring.h>
#include <qwebsocket.h>

class CheckUserCredentialsOperation : public Operation
{
	QWebSocket * ws;
	QString mail;
	QString password;
	int result;

public:
	CheckUserCredentialsOperation(QWebSocket * ws, QString mail, QString password);

	virtual void run();
	virtual void onOperationDone();
};

