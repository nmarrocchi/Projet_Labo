#pragma once

#include <qthread.h>
#include <qlist.h>
#include <QObject>
#include <cstdint>
#include <cstring>
#include <QMap>
#include <QVariant>
#include "uFCoder.h"
#include "database.h"
#include "user.h"

class ReaderCard : public QThread
{
	Q_OBJECT

protected:
	// - run ReaderCard loop
	virtual void run() override;	

private:
	static ReaderCard * instance;
	database * _db;
	user * _user;
	// - Open Reader & loop read function
	ReaderCard(database * db);
	UFR_STATUS status;
	uint32_t readerType = 0;
	uint8_t  cardType = 0;
	uint32_t cardSerial = 0;

public slots:
	// - Create ReaderCard Instance
	static ReaderCard * getInstance(database * db);
	// - Read Card
	void read();

signals:
	// - get read card informations
	void hasRead(QMap< QString, QVariant >);

};