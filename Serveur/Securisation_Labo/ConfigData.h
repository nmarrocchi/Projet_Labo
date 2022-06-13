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

	static ConfigData * instance;
};

