#pragma once
#include "Operation.h"
#include "database.h"

#include <qdatetime.h>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QtNetwork>

class mail : public Operation
{
public:
	/* Constructor mail class */
	mail(int sensorByte, int room);

	/* Run mail thread */
	virtual void run();

	/* Process when the thread is done */
	virtual void onOperationDone();

private:
	int sensorByte;
	int room;

	QString roomName;
	QString sensor;
	QString messageContent;

	/* Write mail content */
	QString message();
};

