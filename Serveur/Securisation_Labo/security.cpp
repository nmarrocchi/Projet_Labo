#include "security.h"

/* Send the statut continuity on the client */
void continuity::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = PCI_7248->readCard(i, 0, 0);

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
	db->updatedb("security", value);
	
}

/* Send the statut sensor on the client */
void sensor::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = PCI_7248->readCard(i, 1, 0);

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
	db->updatedb("security", value);

}

/* Send the statut tamper on the client */
void tamper::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = PCI_7248->readCard(i, 2, 0);

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
	db->updatedb("security", value);

}

/* Send the statut presence on the client */
void presence::selectStatut()
{
	for (int i = 0; i <= 2; i++)
	{
		actualState[i] = PCI_7248->readCard(i, 3, 0);

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
	db->updatedb("security", value);

}