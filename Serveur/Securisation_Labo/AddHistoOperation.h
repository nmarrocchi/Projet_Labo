#pragma once
#include "security.h"
#include "Operation.h"

class AddHistoOperation : public Operation
{
	security * sensor;
	int value;
	bool statut;

public:
	AddHistoOperation(int value, bool statut);

	virtual void run();
	virtual void onOperationDone();
};

