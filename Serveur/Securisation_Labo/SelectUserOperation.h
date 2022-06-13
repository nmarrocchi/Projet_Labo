#pragma once
#include "Operation.h"
#include "webServer.h"
#include "SendUserResultOperation.h"

#include <qsqlquery.h>
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
	/* Constructor SelectUserOperation class */
	SelectUserOperation(QWebSocket * ws);

	/* Run SelectUserOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

