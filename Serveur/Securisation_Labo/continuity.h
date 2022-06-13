#pragma once

#include "security.h"
#include "SensorStateChangedOperation.h"
#include "AddHistoOperation.h"

class continuity : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	/* Construct continuity class */
	continuity(PCI_7248_Card * card, database * db);

	/* Send the statut continuity on the client */
	virtual QList<bool> selectStatut();

	/* Update the statut continuity in database */
	virtual void insertValue(bool status, int room);

private:

	int room;
};