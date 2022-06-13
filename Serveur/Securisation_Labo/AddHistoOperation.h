#pragma once
#include "Operation.h"
#include "security.h"
#include "webServer.h"
#include "SendAddHistoOperation.h"

class AddHistoOperation : public Operation
{
	security * sensor;
	webServer * webserver;

	int value;
	bool statut;

	QString roomValue;
	QString byteValue;
	QString statutValue;
	QString dateValue;

public:
	/* Constructor AddHistoOperation class */
	AddHistoOperation(int value, bool statut);

	/* Run AddHistoOperation thread */
	virtual void run();

	/* Update values on historical on client */
	void actualiseHisto();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

