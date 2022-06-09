#include "continuity.h"
#include "SensorStateChangedOperation.h"
#include "AddHistoOperation.h"

/* Send the statut continuity on the client */
QList<bool> continuity::selectStatut()
{
	QList<bool> result;
	coord.Y = continuityCoordY;

	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 0);
		result.push_back(actualState[i]);

		coord.X = continuityCoordX + largeur * i;

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

/* Update the statut continuity in database */
void continuity::insertValue(bool status, int room)
{
	int value = room * 4 + Byte::continuity + 1;

	database::getInstance()->addOperation(new AddHistoOperation(value, statut));
}