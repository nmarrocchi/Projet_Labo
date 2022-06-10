#include "ManageUserOperation.h"
#include <qsqlquery.h>

ManageUserOperation::ManageUserOperation(QString manage, QString idCard, QString mail, QString password, QString admin)
{
	this->manage = manage;
	this->idCard = idCard;
	this->mail = mail;
	this->password = password;
	this->admin = admin;
}

void ManageUserOperation::run()
{
	QSqlQuery query;

	if (this->manage == "addUser")
	{
		query.exec("INSERT INTO `user`(`idCard`, `mail`, `password`, `isAdmin`) VALUES ('" + idCard + "', '" + mail +"', '" + password +"', '" + admin +"')");
	}
	else if (this->manage == "updateUser") 
	{
		query.exec("UPDATE `user` SET `mail`='" + mail + "',`password`='" + password + "',`isAdmin`='" + admin + "' WHERE `idCard`='" + idCard + "'");
	}
	else if (this->manage == "deleteUser")
	{
		query.exec("DELETE FROM `user` WHERE `idCard`='" + idCard + "'");
	}
}

void ManageUserOperation::onOperationDone()
{
}
