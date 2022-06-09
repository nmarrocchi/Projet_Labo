#include "presence.h"
#include "SensorStateChangedOperation.h"
#include "AddHistoOperation.h"

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

		if (actualState[i] == 0)
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Red);
			qDebug() << "false";

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

			if (lastState[i] != actualState[i])
			{
				insertValue(actualState[i], i);
			}
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