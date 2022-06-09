#include "CheckUserCredentialsOperation.h"
#include <qsqlquery.h>
#include "webServer.h"
#include "SendAuthResultOperation.h"

CheckUserCredentialsOperation::CheckUserCredentialsOperation(QWebSocket * ws, QString mail, QString password)
{
	this->ws = ws;
	this->mail = mail;
	this->password = password;
	result = 0;
}

void CheckUserCredentialsOperation::run()
{
	QSqlQuery query;
	query.exec("SELECT COUNT(*) FROM user WHERE `mail`='" + mail + "' AND `password`='" + password + "'");

	if (query.next())
	{
		result = query.value(0).toInt();
	}
}

void CheckUserCredentialsOperation::onOperationDone()
{
	webServer::getInstance()->addOperation(new SendAuthResultOperation(ws, result));
}
