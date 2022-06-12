#pragma once
#include "Operation.h"

#include <qstring.h>
#include <qsqlquery.h>

class ManageUserOperation : public Operation
{
	QString manage;

	QString idCard;
	QString mail;
	QString password;
	QString admin;

public:
	/* Constructor ManageUserOperation class */
	ManageUserOperation(QString manage, QString idCard, QString mail, QString password, QString admin);

	/* Run ManageUserOperation thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();
};

