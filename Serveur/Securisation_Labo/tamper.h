#pragma once

#include "security.h"
#include "SensorStateChangedOperation.h"
#include "AddHistoOperation.h"

class tamper : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	/* Construct tamper class */
	tamper(PCI_7248_Card * card, database * db);

	/* Send the statut tamper on the client */
	virtual QList<bool> selectStatut();

	/* Update the statut tamper in database */
	virtual void insertValue(bool status, int room);

private:

	int room;
};