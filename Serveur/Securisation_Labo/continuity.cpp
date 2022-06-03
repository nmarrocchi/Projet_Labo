#include "continuity.h"

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

/* Update the statut continuity in database */
void continuity::updateStatut(bool status, int room)
{

	QString value = "status = " + QString::number(status) + " WHERE room = " + QString::number(room);
	//db->updatedb("security", value);

}