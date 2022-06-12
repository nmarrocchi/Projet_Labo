#pragma once
#include "Operation.h"
#include "webServer.h"
#include "SendAuthResultOperation.h"

#include <qstring.h>
#include <qwebsocket.h>
#include <qsqlquery.h>

class CheckUserCredentialsOperation : public Operation
{
	QWebSocket * ws;
	QString mail;
	QString password;
	int result;
	int isAdmin;

public:
	/* Constructor CheckUserCredentialsOperation class */
	CheckUserCredentialsOperation(QWebSocket * ws, QString mail, QString password);

	/* Run CheckUserCredentialsOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

