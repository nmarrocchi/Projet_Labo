#include "tamper.h"

/* Construct tamper class */
tamper::tamper(PCI_7248_Card * card, database * db)
	: security(card)
{
	this->db = db;
}

/* Send the statut tamper on the client */
QList<bool> tamper::selectStatut()
{
	QList<bool> result;
	coord.Y = tamperCoordY;

	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 2);
		result.push_back(actualState[i]);

		coord.X = tamperCoordX + largeur * i;

		// Verification of sensor state
		if (actualState[i] == 0)
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Red);
			qDebug() << "false";

			// Verification with preceding state
			if (lastState[i] != actualState[i])
			{
				database::getInstance()->addOperation(new SensorStateChangedOperation(this, actualState[i], 2, i));
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

/* Update the statut tamper in database */
void tamper::insertValue(bool status, int room)
{
	int value = room * 4 + Byte::tamper + 1;

	database::getInstance()->addOperation(new AddHistoOperation(value, statut));
}