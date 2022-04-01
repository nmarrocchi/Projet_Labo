#pragma once

#include "security.h"

class presence : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	presence(database * db)
	{
		this->db = db;
	}

	virtual void selectStatut();

	virtual void updateStatut(bool status, int room);

private:

	int room;
};