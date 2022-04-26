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
		//exit(0);
	}
}

database::~database()
{}


// - Select Query
QString * database::selectdb(QString table, QString condition)
{
	QSqlQuery selectQuery;
	selectQuery.prepare("SELECT * FROM " + table + condition);
	qDebug() << selectQuery.lastQuery() << endl;
	QString results[4];
	if (selectQuery.exec()) {
		qDebug() << "Data Selected" << endl;

		selectQuery.next();
		for (int i = 0; i < 4; i++)
		{
			results[i] = selectQuery.value(i).toString();
			qDebug() << "Query Result : " + selectQuery.value(i).toString() << endl;
		}
		
		return results;
	}
	else {
		qDebug() << "Data not Selected \n" << endl;
		return results;
	}
}


// - Insert Query
void  database::insertdb(QString table, QString values, QString condition)		

{
	QSqlQuery insertQuery;
	insertQuery.prepare("INSERT INTO " + table + " " + condition);
}

// - Update Query
void  database::updatedb(QString table, QString values, QString condition)
{
	QSqlQuery updateQuery;
	updateQuery.prepare("UPDATE " + table + " SET " + values);
}

// - Delete Query
void  database::deletedb(QString table, QString condition)
{
	QSqlQuery deleteQuery;
	deleteQuery.prepare("DELETE FROM " + table + " WHERE " + condition);
}

// - Select Count(*)
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