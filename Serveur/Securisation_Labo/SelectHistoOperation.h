#pragma once
#include "Operation.h"
#include <qstring.h>
#include <qwebsocket.h>

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
	SelectHistoOperation(QWebSocket * ws);

	virtual void run();
	virtual void onOperationDone();
};

