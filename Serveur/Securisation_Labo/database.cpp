#include "database.h"

#include <qsqlquery.h>


// - Construct Of database class
database::database()
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

database::~database()
{}


// - Select Query
QString * database::selectdb(QString table, QString condition)
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
void  database::insertdb(QString table, QString values, QString condition)
{
	QString query = "INSERT INTO " + table + " " + condition;
}

// - Update Query
void  database::updatedb(QString table, QString values, QString condition)
{
	QString query = "UPDATE " + table + " SET " + value;
}

// - Delete Query
void  database::deletedb(QString table, QString condition)
{
	QString query = "DELETE FROM " + table + " WHERE " + value;
}

// - Select Count(*)
int countdb(QString table, QString condition)
{
	QString query = "SELECT COUNT(*) FROM " + table + " WHERE " + condition;
}