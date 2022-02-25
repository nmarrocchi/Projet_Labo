#pragma once

#include <QObject>
#include <qdebug.h>

class BDD
{
	void selectdb(QString table);

	void insertdb(QString table, QString value);

	void updatedb(QString table, int id, QString value);

	void deletedb(QString table, int id);
};

