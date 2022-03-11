#include "security.h"

/* Constructeur */
security::security(database * db)
{
	this->db = db;
}

/* Destructeur */
security::~security()
{
}

/* Setup security class */
void security::setSecurityById(int idSecurity)
{
}

/* Setup security class by ID */
void security::getIdSecurity()
{
	//selectdb();
}

/* Return the room in database */
void security::getRoom()
{
}

/* Return the bit in database */
void security::getBit()
{
}

/* Return the bit in database */
void security::getStatut()
{
}

/* Return a historic table of sensor/activator in database */
void security::histoSecurity()
{
}

/* Send the statut on the client */
bool continuity::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		//actualState[i] = DO_ReadLine(CardNumber, i, 0, &continuty);

		qDebug() << actualState[i];

		if (lastState[i] != actualState[i])
		{

		}

		lastState[i] = actualState[i];
	}
	return 0;
}

/* Update the statut in database */
void continuity::updateStatut()
{
}
