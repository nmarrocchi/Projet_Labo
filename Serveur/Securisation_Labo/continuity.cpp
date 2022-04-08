#include "continuity.h"

/* Send the statut continuity on the client */
void continuity::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 0);

		if (actualState[i] == 0)
		{
			qDebug() << "Etat continuty false room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat continuty change room: " << i;
				//continuity::updateStatue(actualState[i], i);
				//mail::sendMail();
			}
		}
		else
		{
			qDebug() << "Etat continuty true room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat continuty change room: " << i;
				//continuity::updateStatut(actualState[i], i);
			}
		}

		lastState[i] = actualState[i];

	}
}

/* Update the statut continuity in database */
void continuity::updateStatut(bool status, int room)
{

	QString value = "status = " + QString::number(status) + " WHERE room = " + QString::number(room);
	//db->updatedb("security", value);

}