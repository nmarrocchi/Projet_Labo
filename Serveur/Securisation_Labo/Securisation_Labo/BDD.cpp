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
void BDD::selectdb(QString table, QString condition)
{

	QSqlQuery SelectQuery;

	SelectQuery.prepare("SELECT * FROM " + table + condition);
	qDebug() << SelectQuery.lastQuery() << endl;

	if (SelectQuery.exec()) {
		qDebug() << "Data Selected \n" << endl;

	}
	else {
		qDebug() << "Data not Selected \n" << endl;
	}
}


// - Insert Query
void BDD::insertdb(QString table, QString value1, QString value2)
{
	QString requete = "INSERT INTO " + table;
}

// - Delete Query
void BDD::deletedb(QString table, QString value)
{
	QString requete = "DELETE FROM " + table + " WHERE " + value;
}


// - Update Query
void BDD::updatedb(QString table, QString value)
{
	QString requete = "UPDATE " + table + " SET " + value;
}