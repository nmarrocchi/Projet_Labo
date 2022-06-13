#include "SelectUserOperation.h"

/* Constructor SelectUserOperation class */
SelectUserOperation::SelectUserOperation(QWebSocket * ws)
{
	this->ws = ws;
}

/* Run SelectUserOperation thread */
void SelectUserOperation::run()
{
	QSqlQuery query;

	// Select all values on historical table in database
	query.exec("SELECT * FROM `user`");

	while (query.next())
	{
		idCard = query.value(0).toString();
		mail = query.value(1).toString();
		password = query.value(2).toString();
		admin = query.value(3).toString();

		result = idCard + ";" + mail + ";" + password + ";" + admin;

		// Send result values on SendHistoResultOperation class
		webServer::getInstance()->addOperation(new SendUserResultOperation(ws, result));
	}
}

/* Process when the thread is done */
void SelectUserOperation::onOperationDone()
{
}
