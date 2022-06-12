#include "database.h"
#include <qsqlquery.h>

// - Set database Instance to NULL
database * database::instance = NULL;

// - Create database Instance
database * database::getInstance()
{
	if (instance == NULL)
	{
		database * db = new database();
		instance = db;
	}

	return instance;
}

/* Return request result */
Operation * database::getOperation()
{
	Operation * result = nullptr;
	operationMutex.lock();
	if (operationQueue.size() > 0)
	{
		result = operationQueue.front();
		operationQueue.pop_front();
	}
	operationMutex.unlock();
	return result;
}

// - Constructor of database class
database::database()
{
	ConfigData * config = ConfigData::getInstance();
	this->_Hostname = config->getHostname();
	this->_Username = config->getUsername();
	this->_Password = config->getPassword();
	this->_Database = config->getDatabase();

	start();
}

database::~database()
{}


// - Select Informations in database
QSqlQuery database::selectdb(QString table, QString condition)
{
	QSqlQuery selectQuery;
	selectQuery.prepare("SELECT * FROM " + table + condition);

	if (selectQuery.exec()) 
	{
		return selectQuery;
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

/* Add operation in the queue */
void database::addOperation(Operation * operation)
{
	if (operation != nullptr)
	{
		operationMutex.lock();
		operationQueue.push_back(operation);
		operationMutex.unlock();
	}
}

/* Run database thread */
void database::run()
{
	// - Connecting to mysql database
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(_Hostname);
	db.setUserName(_Username);
	db.setPassword(_Password);
	db.setDatabaseName(_Database);

	// Verification connection with database
	if (db.open())
	{
		qDebug() << endl << "Database connection: Success" << endl;
	}
	else {
		qDebug() << endl << "Database connection: Failed";
		qDebug() << db.lastError() << endl;
		system("PAUSE");
		exit(0);
	}

	while (1)
	{
		// Check if task on operation exist
		Operation * operation = getOperation();
		if (operation != nullptr)
		{
			// Process task on operation
			operation->runTask();
		}
		else
		{
			QThread::msleep(1);
		}
	}
}
