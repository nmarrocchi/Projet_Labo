#include "ManageUserOperation.h"

/* Constructor ManageUserOperation class */
ManageUserOperation::ManageUserOperation(QString manage, QString idCard, QString mail, QString password, QString admin)
{
	this->manage = manage;
	this->idCard = idCard;
	this->mail = mail;
	this->password = password;
	this->admin = admin;
}

/* Run ManageUserOperation thread */
void ManageUserOperation::run()
{
	QSqlQuery query;

	// Verification manage value to execute query
	if (this->manage == "addUser")
	{
		// Insert user values on database
		query.exec("INSERT INTO `user`(`idCard`, `mail`, `password`, `isAdmin`) VALUES ('" + idCard + "', '" + mail +"', '" + password +"', '" + admin +"')");
	}
	else if (this->manage == "updateUser") 
	{
		// Update user values on database
		query.exec("UPDATE `user` SET `mail`='" + mail + "',`password`='" + password + "',`isAdmin`='" + admin + "' WHERE `idCard`='" + idCard + "'");
	}
	else if (this->manage == "deleteUser")
	{
		// Delete user on database
		query.exec("DELETE FROM `user` WHERE `idCard`='" + idCard + "'");
	}
}

/* Process when the thread is done */
void ManageUserOperation::onOperationDone()
{
}
