#pragma once
#include <qobject.h>
#include <qdebug.h>
#include <qmutex.h>
#include <qthread.h>
#include <deque>

#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlerror.h>

#include "Operation.h"
#include "ConfigData.h"

class database : public QThread
{

private:
	QSqlDatabase db;
	QString _Hostname;
	QString _Username;
	QString _Password;
	QString _Database;

	static database * instance;

	std::deque<Operation*> operationQueue;
	QMutex operationMutex;

	/* Return request result */
	Operation * getOperation();

public:
	QString user_table = "user";
	QString passage_table = "passage";
	QString timeSlot_table = "timeSlot";
	QString security_table = "security";
	QString histo_Security_Table = "histo-Security";

	// - Constructor of database class
	database();

	// - Destructor of database class
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

	/* Add operation in the queue */
	void addOperation(Operation * operation);

	/* Run database thread */
	virtual void run() override;
};
