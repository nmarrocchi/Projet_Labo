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

class ReaderCard : public QThread
{
	Q_OBJECT

protected:

	virtual void run() override;	

private:
	static ReaderCard * instance;
	database * _db;
	ReaderCard(database * db);
	UFR_STATUS status;
	uint32_t readerType = 0;
	uint8_t  cardType = 0;
	uint32_t cardSerial = 0;

public slots:
	static ReaderCard * getInstance(database * db);
	void read();
	void write(QString newContent);

signals:
	void hasRead(QMap< QString, QVariant >);

};