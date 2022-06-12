#include "presence.h"

/* Construct presence class */
presence::presence(PCI_7248_Card * card, database * db)
	: security(card)
{
	this->db = db;
}

/* Send the statut presence on the client */
QList<bool> presence::selectStatut()
{
	QList<bool> result;

	coord.Y = presenceCoordY;

	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 3);
		result.push_back(actualState[i]);

		coord.X = presenceCoordX + largeur * i;

		// Verification of sensor state
		if (actualState[i] == 0)
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Red);
			qDebug() << "false";

			// Verification with preceding state
			if (lastState[i] != actualState[i])
			{
				database::getInstance()->addOperation(new SensorStateChangedOperation(this, actualState[i], i));
			}
		}
		else
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Green);
			qDebug() << "true ";

		}

		lastState[i] = actualState[i];
		SetConsoleTextAttribute(handle, text_color::White);
	}
	return result;
}

/* Update the statut presence in database */
void presence::insertValue(bool statut, int room)
{
	int value = room * 4 + Byte::presence + 1;

	database::getInstance()->addOperation(new AddHistoOperation(value, statut));
}