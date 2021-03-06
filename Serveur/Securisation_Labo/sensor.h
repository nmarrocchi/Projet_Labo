#pragma once

#include "security.h"
#include "SensorStateChangedOperation.h"
#include "AddHistoOperation.h"

class sensor : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	/* Construct sensor class */
	sensor(PCI_7248_Card * card, database * db);

	/* Send the statut sensor on the client */
	virtual QList<bool> selectStatut();

	/* Update the statut sensor in database */
	virtual void insertValue(bool status, int room);

private:

	int room;
};