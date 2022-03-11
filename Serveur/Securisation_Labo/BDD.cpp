#include "BDD.h"

#include <qsqlquery.h>


// - Construct Of BDD class
BDD::BDD()
{

	// - Connecting to mysql database
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(_Hostname);
	db.setUserName(_Username);
	db.setPassword(_Password);
	db.setDatabaseName(_Database);

	if (db.open()) {
		qDebug() << "\n Database connected successfully \n" << endl;
	}
	else {
		qDebug() << "\n Database is not connected \n" << endl;
		exit(0);
	}
}

BDD::~BDD()
{}


// - Select Query
QString * BDD::selectdb(QString table, QString condition)
{
	query.prepare("SELECT * FROM " + table + condition);
	qDebug() << query.lastQuery() << endl;

	if (query.exec()) {
		qDebug() << "Data Selected" << endl;

		query.next();

		QString results[4];

		results[1] = query.value(0).toString();
		results[2] = query.value(1).toString();
		results[3] = query.value(2).toString();
		results[4] = query.value(3).toString();

		return results;
	}
	else {
		qDebug() << "Data not Selected \n" << endl;
	}
}


// - Insert Query
void  BDD::insertdb(QString table, QString value1, QString value2, QString condition)
{
	QString query = "INSERT INTO " + table + " " + condition;
}

// - Delete Query
void  BDD::deletedb(QString table, QString value)
{
	QString query = "DELETE FROM " + table + " WHERE " + value;
}


// - Update Query
void  BDD::updatedb(QString table, QString value)
{
	QString query = "UPDATE " + table + " SET " + value;
}