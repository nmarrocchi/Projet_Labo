#pragma once

#include "security.h"

class sensor : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	sensor(PCI_7248_Card * card, database * db)
		: security(card)
	{
		this->db = db;
	}

	virtual void selectStatut();

	virtual void updateStatut(bool status, int room);

private:

	int room;
};