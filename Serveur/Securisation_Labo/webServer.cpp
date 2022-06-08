#include "webServer.h"

// - Set securitySystem Instance to NULL
webServer * webServer::instance = NULL;

// - Create securitySystem Instance
webServer * webServer::getInstance(quint16 port)
{
	if (instance == NULL)
	{
		database * db = database::getInstance();

		instance = new webServer(db, port);
	}

	return instance;
}

void webServer::updateSystemData(SystemData data)
{
	systemDataMutex.lock();
	this->systemState = data;
	systemDataMutex.unlock();
}

webServer::webServer(database * db, quint16 port)
{
	this->webSocketServer = new QWebSocketServer(QStringLiteral("Server WebSocket"), QWebSocketServer::NonSecureMode);

	if (this->webSocketServer->listen(QHostAddress::AnyIPv4, port))
	{
		this->_db = db;

		qDebug() << "WebSocket Server: New connexion on the port " << port << "\n";

		QObject::connect(webSocketServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
	}
	else
	{
		qDebug() << "WebSocket Server: Error connexion on the port " << port << "\n";
	}
}

void webServer::onNewConnection()
{
	webSocket = this->webSocketServer->nextPendingConnection();

	QObject::connect(webSocket, SIGNAL(textMessageReceived(const QString&)), this, SLOT(processTextMessage(const QString&)));

	QObject::connect(webSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

	this->wsclients.push_back(webSocket);
}

// Receive All message of the WebSocket
void webServer::processTextMessage(const QString& message) {

	QWebSocket * ws = qobject_cast<QWebSocket*>(sender());

	// Request connexion client
	if (message.startsWith("Auth") == true)
	{
		// Section message
		QString data = QStringRef(&message, 4, message.length() - 4).toString();
		QString mail = data.section(";", 0, 0);
		QString password = data.section(";", 1, 1);

		QSqlQuery query;
		query.exec("SELECT COUNT(*) FROM user WHERE `mail`='" + mail + "' AND `password`='" + password + "'");


		int result;

		if (query.next())
		{
			result = query.value(0).toInt();
		}

		// Send result on client
		ws->sendTextMessage("Auth;" + QString::number(result));
	}

	if (message.startsWith("State") == true)
	{
		QString val;
		QString data = "State";

		SystemData dataCpy;
		systemDataMutex.lock();
		dataCpy = systemState;
		systemDataMutex.unlock();

		for (int j = 0; j < 4; j++)
		{
			switch (j)
			{
			case 0:

				val = "Continuity";
				data += ";" + val;

				for (int i = 0; i < 3; i++)
				{
					bool dataValue = dataCpy.getContinuityStates()[i];

					if (dataValue == false)
					{
						val = "false";
					}
					else {
						val = "true";
					}

					data += ";" + val;
				}

				break;

			case 1:

				val = "Sensor";
				data += ";" + val;

				for (int i = 0; i < 3; i++)
				{
					bool dataValue = dataCpy.getSensorStates()[i];

					if (dataValue == false)
					{
						val = "false";
					}
					else {
						val = "true";
					}

					data += ";" + val;
				}

				break;

			case 2:

				val = "Tamper";
				data += ";" + val;

				for (int i = 0; i < 3; i++)
				{
					bool dataValue = dataCpy.getTamperStates()[i];

					if (dataValue == false)
					{
						val = "false";
					}
					else {
						val = "true";
					}

					data += ";" + val;
				}

				break;

			case 3:

				val = "Presence";
				data += ";" + val;

				for (int i = 0; i < 3; i++)
				{
					bool dataValue = dataCpy.getPresenceStates()[i];

					if (dataValue == false)
					{
						val = "false";
					}
					else {
						val = "true";
					}

					data += ";" + val;
				}

				break;

			default:
				break;
			}
			
		}
		ws->sendTextMessage(data);
	}

	if (message.startsWith("Histo") == true)
	{
		/*
		QSqlQuery query;
		query.exec("SELECT security.room, security.byte, historical.statut, historical.date FROM historical, security WHERE security.idSecurity = historical.idSecurity");

		QString tab[6] = { "Continuity", "Sensor", "Tamper", "Presence", "Alarm", "Siren" };

		while (query.next())
		{
			QString roomValue = query.value(0).toString();
			QString byteValue = query.value(1).toString();
			QString statutValue = query.value(2).toString();
			QString dateValue = query.value(3).toString();

			if (statutValue == "1")
			{
				statutValue = "true";
			}
			else
			{
				statutValue = "false";
			}

			int rand = QRandomGenerator::global()->bounded(6);

			byteValue = tab[rand];

			QString data = "Histo;" + roomValue + ";" + byteValue + ";" + statutValue + ";" + dateValue;

			ws->sendTextMessage(data);
		}
		*/
	}
}

void webServer::socketDisconnected()
{

	qDebug() << "Server WebSocket: Deconnexion\n";
}