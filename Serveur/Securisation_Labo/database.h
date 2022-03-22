#pragma once
#include <qobject.h>
#include <qdebug.h>

#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>

class database
{

private:
	QSqlDatabase db;
	QString _Hostname = "192.168.65.219";
	QString _Username = "admin";
	QString _Password = "admin";
	QString _Database = "labo";


public:

	database();
	~database();

	QString * selectdb(QString table, QString condition);
	void insertdb(QString table, QString values, QString condition);
	void updatedb(QString table, QString values, QString condition);
	void deletedb(QString table, QString condition);
	int countdb(QString table, QString condition);

protected:
	QSqlQuery query;
	QString user_table = "user";
	QString passage_table = "passage";
	QString timeSlot_table = "timeSlot";
	QString security_table = "security";
	QString histo_Security_Table = "histo-Security";

};
