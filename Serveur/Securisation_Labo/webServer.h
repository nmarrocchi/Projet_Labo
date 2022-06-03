#pragma once

#include <QObject>
#include <QSettings>
#include <QWebSocket>
#include <QWebSocketServer>
#include <qfile.h>

#include "database.h"

class webServer : public QObject {

	Q_OBJECT

		QWebSocketServer *webSocketServer;
		QWebSocket * webSocket;
		QList<QWebSocket*> wsclients;

private:
	static webServer * instance;
	database * _db;

	webServer(database * db, quint16 port);

public:
	static webServer * getInstance(database * db, quint16 port);

private slots:

	void onNewConnection();
	void processTextMessage(const QString& message);
	void socketDisconnected();
};
