#pragma once

#include "database.h"
#include "PCI_7248.h"

class security
{

public:

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

	PCI_7248 *PCI_7248;

};

class continuity : public security
{

	bool actualState[3];
	bool lastState[3];

public:

	continuity(database * db)
	{
		this->db = db;
	}

	virtual void selectStatut();

	virtual void updateStatut(bool status, int room);

private:

	int room;

};

class sensor : public security
{

};

class tamper : public security
{

};

class presence : public security
{

};