#pragma once

#include "security.h"

class presence : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	/* Construct presence class */
	presence(PCI_7248_Card * card, database * db)
		: security(card)
	{
		this->db = db;
	}

	/* Send the statut presence on the client */
	virtual QList<bool> selectStatut();

	/* Update the statut presence in database */
	virtual void updateStatut(bool status, int room);

private:

	int room;
};