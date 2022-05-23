#pragma once

#include <QObject>
#include <QSettings>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QTimer>
#include <qfile.h>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Server : public QObject {

	Q_OBJECT

public:
	Server(QObject *parent = Q_NULLPTR);
	~Server();

private:
	QWebSocketServer *webServer;

	std::vector< QWebSocket * > etabishedConnection;

public slots:
	void onWebServerNewConnection();
	void onWebClientDisconnected();
};
