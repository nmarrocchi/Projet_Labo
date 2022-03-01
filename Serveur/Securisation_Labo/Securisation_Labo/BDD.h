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
	BDD(QString Hostname, QString Username, QString Password, QString Database);

	~BDD();

	private:
		QString Hostname = "192.168.65.219";
		QString Username = "admin";
		QString Password = "admin";
		QString Database = "labo";

	public:
		

		void selectdb(QString table);
		void insertdb(QString table, QString value);
		void updatedb(QString table, int id, QString value);
		void deletedb(QString table, int id);

};

// - Construct Of BDD class
BDD::BDD(QString Hostname, QString Username, QString Password, QString Database)
{
	QSqlDatabase BDD = QSqlDatabase::addDatabase("QMYSQL");
	BDD.setHostName(Hostname);
	BDD.setUserName(Username);
	BDD.setPassword(Password);
	BDD.setDatabaseName(Database);
	if (BDD.open())
	{
		printf("Vous êtes maintenant connecté");
		BDD.close();
	}
	else
	{
		printf("La connexion a échouée, désolé");
	}
}


// - Select Query
void BDD::selectdb(QString table)
{
	QString requete = "SELECT * FROM" + table ;
}


// - Insert Query
void insertdb(QString table, QString value)
{
	QString requete = "INSERT INTO" + table;
}


// - Update Query
void updatedb(QString table, int id, QString value)
{
}


// - Delete Query
void deletedb(QString table, int id)
{
}




