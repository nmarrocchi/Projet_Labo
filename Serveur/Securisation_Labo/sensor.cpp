#include "sensor.h"

/* Construct sensor class */
sensor::sensor(PCI_7248_Card * card, database * db)
	: security(card)
{
	this->db = db;
}

/* Send the statut sensor on the client */
QList<bool> sensor::selectStatut()
{
	QList<bool> result;
	coord.Y = sensorCoordY;

	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 1);
		result.push_back(actualState[i]);

		coord.X = sensorCoordX + largeur * i;

		// Verification of sensor state
		if (actualState[i] == 0)
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Red);
			qDebug() << "false";

			// Verification with preceding state
			if (lastState[i] != actualState[i])
			{
				database::getInstance()->addOperation(new SensorStateChangedOperation(this, actualState[i], 1, i));
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

	/* Update the statut sensor in database */
void sensor::insertValue(bool status, int room)
{
	int value = room * 4 + Byte::sensor + 1;

	database::getInstance()->addOperation(new AddHistoOperation(value, statut));
}