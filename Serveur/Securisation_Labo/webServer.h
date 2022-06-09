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
#include <qtimer.h>
#include <deque>

class webServer : public QObject {

	Q_OBJECT

		QWebSocketServer *webSocketServer;
		QWebSocket * webSocket;
		QList<QWebSocket*> wsclients;
		SystemData systemState;
		QMutex systemDataMutex;


		std::deque<Operation*> operationQueue;
		QMutex operationMutex;

		QTimer operationTimer;

private:
	static webServer * instance;
	database * _db;

	webServer(database * db, quint16 port);

	Operation * getOperation();

public:
	static webServer * getInstance(quint16 port = 0);

	void updateSystemData(SystemData data);

	void addOperation(Operation * operation);

private slots:

	void onNewConnection();
	void processTextMessage(const QString& message);
	void socketDisconnected();

	void operationTimerTick();
};
