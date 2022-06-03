#include "database.h"
#include <qsqlquery.h>


// - Constructor of database class
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
		//exit(0);
	}
}

database::~database()
{}


// - Select Informations in database
QSqlQuery database::selectdb(QString table, QString condition)
{
	QSqlQuery selectQuery;
	selectQuery.prepare("SELECT * FROM " + table + condition);

	if (selectQuery.exec()) {
		qDebug() << "Request executed" << endl;
		
		return selectQuery;
	}
	else {
		qDebug() << "Request not executed" << endl;
	}
}


// - Insert Informations in database
void  database::insertdb(QString table, QString values, QString condition)	

{
	QSqlQuery insertQuery;
	insertQuery.prepare("INSERT INTO " + table + " " + condition);
}

// - Update Informations in database
void  database::updatedb(QString table, QString values, QString condition)
{
	QSqlQuery updateQuery;
	updateQuery.prepare("UPDATE " + table + " SET " + values);
}

// - Delete Informations in database
void  database::deletedb(QString table, QString condition)
{
	QSqlQuery deleteQuery;
	deleteQuery.prepare("DELETE FROM " + table + " WHERE " + condition);
}

// - Count data with same information
int database::countdb(QString table, QString condition)
{
	QSqlQuery selectCount;
	selectCount.prepare("SELECT COUNT(*) FROM " + table + condition);

	if (selectCount.exec()) {
		selectCount.next();
		return selectCount.value(0).toInt();
	}

	return 0;

}