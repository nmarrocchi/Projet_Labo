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
	
	QObject::connect(webServer, &QWebSocketServer::newConnection, this, &Server::onWebServerNewConnection);
	
	rfid = new RFID();
	
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), rfid, SLOT(read()));
	connect(rfid, SIGNAL(hasRead(QMap< QString, QVariant >)), this, SLOT(sendCardDetails(QMap< QString, QVariant >)));
	timer->start();

}

void Server::onWebServerNewConnection() {

	QWebSocket *webSocket = webServer->nextPendingConnection();
	
	QTcpSocket::connect(webSocket, &QWebSocket::textMessageReceived, this, &Server::onWebClientCommunication);
	QTcpSocket::connect(webSocket, &QWebSocket::disconnected, this, &Server::onWebClientDisconnected);
	
	(&this->etabishedConnection)->push_back(webSocket);
	qDebug() << "Nouvelle connexion de " << webSocket->peerAddress().toString();

}

void Server::onWebClientCommunication(QString entryMessage) {

	QWebSocket * obj = qobject_cast<QWebSocket *>(sender());
	
	qDebug() << "Demande de modification de la carte : " << entryMessage;
	
	rfid->write(entryMessage);

}

void Server::onWebClientDisconnected() {

	qDebug() << "Client deconnecte";

}


void Server::sendCardDetails(QMap< QString, QVariant > card) {
	
	for (QWebSocket *webSocket : this->etabishedConnection) {
	
		QString formatedTable = card["isset"].toString() + "," + card["cardType"].toString() + "," + card["cardSerial"].toString() + "," + card["data"].toString();
		webSocket->sendTextMessage(formatedTable);
	
	}

}

Server::~Server() {

	qDebug() << "Destruction du serveur";

}