#pragma once
#include "Operation.h"
#include "webServer.h"
#include "SendHistoResultOperation.h"

#include <qstring.h>
#include <qwebsocket.h>
#include <qsqlquery.h>

class SelectHistoOperation : public Operation
{
	QWebSocket * ws;

	QString roomValue;
	QString byteValue;
	QString statutValue;
	QString dateValue;

	QString idCardValue;
	QString mailValue;

	QString resultHisto;
	QString resultPassage;

public:
	/* Constructor SelectHistoOperation class */
	SelectHistoOperation(QWebSocket * ws);

	/* Run SelectHistoOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

