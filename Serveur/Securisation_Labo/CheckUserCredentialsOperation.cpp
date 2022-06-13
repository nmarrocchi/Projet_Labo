#include "CheckUserCredentialsOperation.h"

/* Constructor CheckUserCredentialsOperation class */
CheckUserCredentialsOperation::CheckUserCredentialsOperation(QWebSocket * ws, QString mail, QString password)
{
	this->ws = ws;
	this->mail = mail;
	this->password = password;
	result = 0;
}

/* Run CheckUserCredentialsOperation thread */
void CheckUserCredentialsOperation::run()
{
	QSqlQuery query;

	// Verification if user exist in database
	query.exec("SELECT COUNT(*) FROM user WHERE `mail`='" + mail + "' AND `password`='" + password + "'");

	if (query.next())
	{
		result = query.value(0).toInt();

		// Verification if user is an administrator in database
		query.exec("SELECT `isAdmin` FROM `user` WHERE `mail`='" + mail + "' , `password`='" + password + "'");
		if (query.next()) 
		{
			isAdmin = query.value(0).toInt();
		}
	}
}

/* Process when the thread is done */
void CheckUserCredentialsOperation::onOperationDone()
{
	// Send result at SendAuthResultOperation class
	webServer::getInstance()->addOperation(new SendAuthResultOperation(ws, result, isAdmin));
}
