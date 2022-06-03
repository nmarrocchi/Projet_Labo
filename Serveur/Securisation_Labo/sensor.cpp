#include "sensor.h"

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

		if (actualState[i] == 0)
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Red);
			qDebug() << "false";

			if (lastState[i] != actualState[i])
			{
				if (timeSlot::validateTime() == false)
				{
					//continuity::updateStatue(actualState[i], i);
					//mail::sendMail();
				}
			}
		}
		else
		{
			
			SetConsoleCursorPosition(handle, coord);
			SetConsoleTextAttribute(handle, text_color::Green);
			qDebug() << "true ";

			if (lastState[i] != actualState[i])
			{
				//continuity::updateStatut(actualState[i], i);
			}
		}

		lastState[i] = actualState[i];
		SetConsoleTextAttribute(handle, text_color::White);
	}

	return result;
}

	/* Update the statut sensor in database */
void sensor::updateStatut(bool status, int room)
{

	QString value = "status = " + QString::number(status) + " WHERE room = " + QString::number(room);
	//db->updatedb("security", value);

}