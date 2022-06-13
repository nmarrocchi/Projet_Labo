#pragma once
#include <QtCore/QCoreApplication>
#include <QSettings>

class ConfigData
{
private:
	int port;

	QString hostname;
	QString username;
	QString password;
	QString database;

	QString coursStartTime;
	QString coursEndTime;

public:
	// - Create ConfigData Instance
	static ConfigData * getInstance();

	// - Constructor of ConfigData class
	ConfigData();

	/* Return port value on config.ini file */
	int getPort();

	/* Return hostname value on config.ini file */
	QString getHostname();

	/* Return username value on config.ini file */
	QString getUsername();

	/* Return password value on config.ini file */
	QString getPassword();

	/* Return database value on config.ini file */
	QString getDatabase();

	/* Return start time cours value on config.ini file */
	QString getCoursStartTime();

	/* Return end time cours value on config.ini file */
	QString getCoursEndTime();

	static ConfigData * instance;
};

