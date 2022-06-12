#pragma once
#include "Operation.h"
#include "security.h"

class AddHistoOperation : public Operation
{
	security * sensor;
	int value;
	bool statut;

public:
	/* Constructor AddHistoOperation class */
	AddHistoOperation(int value, bool statut);

	/* Run AddHistoOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

