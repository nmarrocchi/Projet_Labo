#include "Server.h"

Server::Server(QObject *parent) : QObject(parent) {

	webServer = new QWebSocketServer(QStringLiteral("WebServer"), QWebSocketServer::NonSecureMode, this);

	// Open configuration file for reading port number
	QSettings *settings = new QSettings("config.ini", QSettings::IniFormat);

	QStringList list = settings->allKeys();

	if (!settings->contains("PORT/port"))
	{
		settings->beginGroup("PORT");
		settings->setValue("port", "3004");
		settings->endGroup();
		settings->sync();
	}

	int port = settings->value("PORT/port", "config").toInt();

	if (!webServer->listen(QHostAddress::Any, port)) {
		qDebug() << "Error, can't listen on port " << port;
		exit(-1);
	}
	else {
		qDebug() << "Websocket server launched" << endl;
	}

	QObject::connect(webServer, &QWebSocketServer::newConnection, this, &Server::onWebServerNewConnection);

}

void Server::onWebServerNewConnection() {

	QWebSocket *webSocket = webServer->nextPendingConnection();

	QTcpSocket::connect(webSocket, &QWebSocket::disconnected, this, &Server::onWebClientDisconnected);

	(&this->etabishedConnection)->push_back(webSocket);
	qDebug() << "Nouvelle connexion de " << webSocket->peerAddress().toString();

}

void Server::onWebClientDisconnected() {

	qDebug() << "Client deconnecte";

}

Server::~Server() {

	qDebug() << "Destruction du serveur";

}