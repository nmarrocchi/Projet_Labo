#pragma once

#include <QObject>
#include <QSettings>
#include <QWebSocket>
#include <QWebSocketServer>
#include <qfile.h>
#include <qthread.h>
#include <qmutex.h>

#include "database.h"
#include "SystemData.h"

class webServer : public QObject {

	Q_OBJECT

		QWebSocketServer *webSocketServer;
		QWebSocket * webSocket;
		QList<QWebSocket*> wsclients;
		SystemData systemState;
		QMutex systemDataMutex;

private:
	static webServer * instance;
	database * _db;

	webServer(database * db, quint16 port);

public:
	static webServer * getInstance(database * db = NULL, quint16 port = 0);

	void updateSystemData(SystemData data);

private slots:

	void onNewConnection();
	void processTextMessage(const QString& message);
	void socketDisconnected();

	//void receiveSensorState(bool actualState);
};
