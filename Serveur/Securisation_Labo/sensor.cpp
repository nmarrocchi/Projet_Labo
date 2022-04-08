#include "sensor.h"

/* Send the statut sensor on the client */
void sensor::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 1);

		if (actualState[i] == 0)
		{
			qDebug() << "Etat sensor false room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat sensor change room: " << i;
				//continuity::updateStatue(actualState[i], i);
				//mail::sendMail();
			}
		}
		else
		{
			qDebug() << "Etat sensor true room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat sensor change room: " << i;
				//continuity::updateStatut(actualState[i], i);
			}
		}

		lastState[i] = actualState[i];

	}
}

/* Update the statut sensor in database */
void sensor::updateStatut(bool status, int room)
{

	QString value = "status = " + QString::number(status) + " WHERE room = " + QString::number(room);
	//db->updatedb("security", value);

}