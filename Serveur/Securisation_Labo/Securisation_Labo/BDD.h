#pragma once
#include <qobject.h>
#include <qdebug.h>

#include <qtsqlglobal.h>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqldriver.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>

class BDD
{
	//BDD(QString Hostname, QString Username, QString Password, QString Database);

	//~BDD();

	private:
		QString Hostname = "192.168.65.219";
		QString Username = "admin";
		QString Password = "admin";
		QString Database = "labo";

	public:
		

		void selectdb(QString table);
		void insertdb(QString table, QString value);
		void updatedb(QString table, QString value);
		void deletedb(QString table, QString value);

};


