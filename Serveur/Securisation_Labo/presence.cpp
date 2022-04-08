#include "presence.h"

/* Send the statut presence on the client */
void presence::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = card->readCard(i, 3);

		if (actualState[i] == 0)
		{
			qDebug() << "Etat presence false room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat presence change room: " << i;
				//continuity::updateStatue(actualState[i], i);
				//mail::sendMail();
			}
		}
		else
		{
			qDebug() << "Etat presence true room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat presence change room: " << i;
				//continuity::updateStatut(actualState[i], i);
			}
		}

		lastState[i] = actualState[i];

	}
}

/* Update the statut presence in database */
void presence::updateStatut(bool status, int room)
{

	QString value = "status = " + QString::number(status) + " WHERE room = " + QString::number(room);
	//db->updatedb("security", value);

}