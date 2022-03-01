#pragma once

#include "BDD.h"

class security
{
	public:

		/* Constructeur */
		security();

		/* Destructeur */
		~security();

	private slots:
		
		/* Setup security class */
		void setSecurity();

		/* Setup security class by ID */
		void setSecurityById(int idSecurity);

		/* Return the ID in database */
		void getIdSecurity();

		/* Return the room in database */
		void getRoom();

		/* Return the bit in database */
		void getBit();

		/* Return the statut in database */
		void getStatut();

		/* Return a historic table of sensor/activator in database */
		void histoSecurity();

		/* Send the statut on the client */
		void selectStatut();

		/* Update the statut in database */
		void updateStatut();

	private:

		int idSecurity;

		int room;

		int bit;

		int statut;

};

