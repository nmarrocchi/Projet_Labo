#include "AddHistoOperation.h"

/* Constructor AddHistoOperation class */
AddHistoOperation::AddHistoOperation(int value, bool statut)
{
	this->value = value;
	this->statut = statut;

	this->webserver = webServer::getInstance();
}

/* Run AddHistoOperation thread */
void AddHistoOperation::run()
{
	// Insert values in historical in database
	QSqlQuery query;
	query.exec("INSERT INTO `historical`(`idSecurity`, `statut`) VALUES (" + QString::number(value) + ", " + QString::number(statut) + ")");

	actualiseHisto();
}

/* Update values on historical on client */
void AddHistoOperation::actualiseHisto()
{
	QSqlQuery query;

	// Select all values on historical table in database
	query.exec("SELECT security.room, security.byte, historical.statut, DATE_FORMAT(historical.date, '%d/%c/%Y %T') FROM historical, security WHERE security.idSecurity = historical.idSecurity ORDER BY date DESC");
	
	if (query.next())
	{
		roomValue = query.value(0).toString();
		byteValue = query.value(1).toString();
		statutValue = query.value(2).toString();
		dateValue = query.value(3).toString();

		if (statutValue == "1")
		{
			statutValue = "true";
		}
		else
		{
			statutValue = "false";
		}

		QString result = "Sensor;" + roomValue + ";" + byteValue + ";" + statutValue + ";" + dateValue;

		// Send result values on SendAddHistoOperation class
		webServer::getInstance()->addOperation(new SendAddHistoOperation(webserver, result));
	}
}

/* Process when the thread is done */
void AddHistoOperation::onOperationDone()
{
}
