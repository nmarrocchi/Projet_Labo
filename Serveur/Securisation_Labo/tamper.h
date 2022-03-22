#pragma once

#include "security.h"

class tamper : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	tamper(database * db)
	{
		this->db = db;
	}

	virtual void selectStatut();

	virtual void updateStatut(bool status, int room);

private:

	int room;
};