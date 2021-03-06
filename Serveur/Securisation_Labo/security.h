#pragma once

#include <qmutex.h>

#include "database.h"
#include "PCI_7248_Card.h"
#include "timeSlot.h"

#include "lib/ConsoleTableLib/ConsoleTable.h"
#include "lib/text_color-lib/text_color.h"

class security
{

public:
	security(PCI_7248_Card * card);
	
	void loop();

	/* Create a table to supervise the sytheme on the console */
	static void superviseTable();

	/* Send the statut on the client */
	virtual QList<bool> selectStatut() = 0;

	/* Update the statut in database */
	virtual void insertValue(bool status, int room) = 0;

protected:

	int idSecurity;
	int room;
	int bit;
	bool statut;

	database * db;

	PCI_7248_Card *card;

	QMutex systemMutex;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;

	enum Coord
	{
		continuityCoordX	= 15,
		sensorCoordX		= 15,
		tamperCoordX		= 15,
		presenceCoordX		= 15,

		continuityCoordY	= 3,
		sensorCoordY		= 5,
		tamperCoordY		= 7,
		presenceCoordY		= 9,

		largeur				= 8,
		hauteur				= 0,

	};

	enum Byte
	{
		continuity	= 0,
		sensor		= 1,
		tamper		= 2,
		presence	= 3,
	};

};







