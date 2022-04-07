#pragma once

#include "database.h"
#include "PCI_7248_Card.h"

class security
{
public:

	

	void loop();

	/* Send the statut on the client */
	virtual void selectStatut() = 0;

	/* Update the statut in database */
	virtual void updateStatut(bool status, int room) = 0;

protected:

	int idSecurity;

	int room;

	int bit;

	bool statut;

	database *db;

	PCI_7248_Card *card;

};







