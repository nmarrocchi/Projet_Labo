#pragma once
#include <qobject.h>
#include <qdebug.h>

#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <deque>
#include "Operation.h"
#include <qmutex.h>
#include <qthread.h>

class database : public QThread
{

private:
	QSqlDatabase db;
	QString _Hostname = "192.168.65.219";
	QString _Username = "admin";
	QString _Password = "admin";
	QString _Database = "labotest";

	static database * instance;

	std::deque<Operation*> operationQueue;
	QMutex operationMutex;

	Operation * getOperation();

public:
	QString user_table = "user";
	QString passage_table = "passage";
	QString timeSlot_table = "timeSlot";
	QString security_table = "security";
	QString histo_Security_Table = "histo-Security";

	// - Constructor of database class
	database();
	~database();

	static database * getInstance();

	// - Select informations in database
	QSqlQuery selectdb(QString table, QString condition);

	// - Insert Informations in database
	void insertdb(QString table, QString values, QString condition);

	// - Update Informations in database
	void updatedb(QString table, QString values, QString condition);

	// - Delete Informations in database
	void deletedb(QString table, QString condition);

	// - Count data with same information
	int countdb(QString table, QString condition);

	void addOperation(Operation * operation);

	virtual void run() override;
};
