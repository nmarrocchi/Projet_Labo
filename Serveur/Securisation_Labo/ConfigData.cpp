#include "ConfigData.h"

// - Set ConfigData Instance to NULL
ConfigData * ConfigData::instance = NULL;

// - Create ConfigData Instance
ConfigData * ConfigData::getInstance()
{
	if (instance == NULL)
	{
		ConfigData * config = new ConfigData();
		instance = config;
	}

	return instance;
}

// - Constructor of ConfigData class
ConfigData::ConfigData()
{
	QSettings * settings = new QSettings("config.ini", QSettings::IniFormat);

	QStringList list = settings->allKeys();

	if (!settings->contains("WebSocket/port") || !settings->contains("Database/hostname") || !settings->contains("Database/username") 
		|| !settings->contains("Database/password") || !settings->contains("Database/database"))
	{
		settings->beginGroup("WebSocket");
		settings->setValue("port", "2569");
		settings->endGroup();
		settings->sync();

		settings->beginGroup("Database");
		settings->setValue("hostname", "192.168.65.219");
		settings->setValue("username", "admin");
		settings->setValue("password", "admin");
		settings->setValue("database", "labotest");
		settings->endGroup();
		settings->sync();
	}

	this->port		= settings->value("WebSocket/port", "config").toInt();
	this->hostname	= settings->value("Database/hostname", "config").toString();
	this->username	= settings->value("Database/username", "config").toString();
	this->password	= settings->value("Database/password", "config").toString();
	this->database	= settings->value("Database/database", "config").toString();
}

/* Return port value on config.ini file */
int ConfigData::getPort()
{
	return port;
}

/* Return hostname value on config.ini file */
QString ConfigData::getHostname()
{
	return hostname;
}

/* Return username value on config.ini file */
QString ConfigData::getUsername()
{
	return username;
}

/* Return password value on config.ini file */
QString ConfigData::getPassword()
{
	return password;
}

/* Return database value on config.ini file */
QString ConfigData::getDatabase()
{
	return database;
}
