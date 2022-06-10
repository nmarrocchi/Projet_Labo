#include "SelectHistoOperation.h"
#include <qsqlquery.h>
#include "webServer.h"
#include "SendHistoResultOperation.h"

SelectHistoOperation::SelectHistoOperation(QWebSocket * ws)
{
	this->ws = ws;
}

void SelectHistoOperation::run()
{
	QSqlQuery query;
	query.exec("SELECT security.room, security.byte, historical.statut, DATE_FORMAT(historical.date, '%d/%c/%Y %T') FROM historical, security WHERE security.idSecurity = historical.idSecurity ORDER BY date DESC LIMIT 50");

	while (query.next())
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

		QString resultHisto = "Sensor;" + roomValue + ";" + byteValue + ";" + statutValue + ";" + dateValue;

		webServer::getInstance()->addOperation(new SendHistoResultOperation(ws, resultHisto));
	}

	query.exec("SELECT passage.idCard, user.mail, DATE_FORMAT(passage.date, '%d/%c/%Y %T') FROM `passage`, `user` WHERE passage.idCard = user.idCard ORDER BY date DESC LIMIT 50");

	while (query.next())
	{
		idCardValue = query.value(0).toString();
		mailValue = query.value(1).toString();
		dateValue = query.value(2).toString();

		QString resultPassage = "Passage;" + idCardValue + ";" + mailValue + ";" + dateValue;

		webServer::getInstance()->addOperation(new SendHistoResultOperation(ws, resultPassage));
	}
}

void SelectHistoOperation::onOperationDone()
{
}
