#include "mail.h"

/* Constructor mail class */
mail::mail(int sensorByte, int room)
{
	this->sensorByte = sensorByte;
	this->room = room;
}

/* Run mail thread */
void mail::run()
{
	QSqlQuery query;
	
	// Recuperation all admin
	query.exec("SELECT `mail` FROM `user` WHERE `isAdmin`= 1");
	QString admin = "?admin=";

	while (query.next())
	{
		admin += query.value(0).toString() + ";";
	}

	// Send mail
	messageContent = message();
	QString corpsContent = "&corps=" + messageContent;

	const QUrl url = QUrl("http://192.168.64.103/API/labo" + admin + corpsContent);
	const QNetworkRequest requete(url);
	QNetworkAccessManager *m = new QNetworkAccessManager;
	QNetworkReply *r = m->get(requete);
}

/* Process when the thread is done */
void mail::onOperationDone()
{
}

/* Write mail content */
QString mail::message()
{
	if (this->sensorByte == 0)
	{
		sensor = "Continuity";
	}
	else if (this->sensorByte == 1) 
	{
		sensor = "Sensor";
	}
	else if (this->sensorByte == 2)
	{
		sensor = "Tamper";
	}
	else if (this->sensorByte == 3)
	{
		sensor = "Presence";
	}

	if (this->room == 0)
	{
		roomName = "SN1";
	}
	else if (this->room == 1)
	{
		roomName = "SN2";
	}
	else if (this->room == 2)
	{
		roomName = "PHY";
	}

	QString dayNow = QDateTime::currentDateTime().toString("dd/MM/yyyy");
	QString timeNow = QDateTime::currentDateTime().toString("hh:mm:ss");

	messageContent = "Intrusion detectee par le capteur: " + sensor + " dans la salle: " + roomName + " le: " + dayNow + " a " + timeNow;
	return messageContent;
}
