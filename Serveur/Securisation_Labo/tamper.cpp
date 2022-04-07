#include "tamper.h"

/* Send the statut tamper on the client */
void tamper::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		PCI_7248_Card * card = new PCI_7248_Card();
		actualState[i] = card->readCard(i, 2);

		if (actualState[i] == 0)
		{
			qDebug() << "Etat tamper false room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat tamper change room: " << i;
				//continuity::updateStatue(actualState[i], i);
				//mail::sendMail();
			}
		}
		else
		{
			qDebug() << "Etat tamper true room: " << i;
			if (lastState[i] != actualState[i])
			{
				qDebug() << "Etat tamper change room: " << i;
				//continuity::updateStatut(actualState[i], i);
			}
		}

		lastState[i] = actualState[i];

	}
}

/* Update the statut tamper in database */
void tamper::updateStatut(bool status, int room)
{

	QString value = "status = " + QString::number(status) + " WHERE room = " + QString::number(room);
	//db->updatedb("security", value);

}