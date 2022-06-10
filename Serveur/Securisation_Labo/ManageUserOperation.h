#pragma once
#include "Operation.h"
#include <qstring.h>

class ManageUserOperation : public Operation
{
	QString manage;

	QString idCard;
	QString mail;
	QString password;
	QString admin;

public:
	ManageUserOperation(QString manage, QString idCard, QString mail, QString password, QString admin);

	virtual void run();
	virtual void onOperationDone();
};

