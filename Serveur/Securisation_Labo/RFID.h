#pragma once

#include <QWebSocket>
#include <QObject>
#include <cstdint>
#include <cstring>
#include <QMap>
#include "uFCoder.h"
#include "Server.h"
#include "user.h"

class Server;

class RFID : public QObject
{
	Q_OBJECT

public:
	RFID(QObject *parent = Q_NULLPTR);
	~RFID();

private:
	
	user * User;

	UFR_STATUS status;
	uint32_t readerType = 0;
	uint8_t  cardType = 0;
	uint32_t cardSerial = 0;

public slots:
	void read();
	void write(QString newContent);

signals:
	void hasRead(QMap< QString, QVariant >);

};