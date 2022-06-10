#include "SelectUserOperation.h"
#include <qsqlquery.h>
#include "webServer.h"
#include "SendUserResultOperation.h"

SelectUserOperation::SelectUserOperation(QWebSocket * ws)
{
	this->ws = ws;
}

void SelectUserOperation::run()
{
	QSqlQuery query;
	query.exec("SELECT * FROM `user`");

	while (query.next())
	{
		idCard = query.value(0).toString();
		mail = query.value(1).toString();
		password = query.value(2).toString();
		admin = query.value(3).toString();

		result = idCard + ";" + mail + ";" + password + ";" + admin;

		webServer::getInstance()->addOperation(new SendUserResultOperation(ws, result));
	}
}

void SelectUserOperation::onOperationDone()
{
}
