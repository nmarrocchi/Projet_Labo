#include <QtCore/QCoreApplication>

#include "database.h"
#include "security.h"
#include "continuity.h"
#include "sensor.h"
#include "tamper.h"
#include "presence.h"
#include "Server.h"
#include "RFID.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	database *db = new database();
	//user * User = new user();
	Server * server = new Server();
	
	continuity * cont	= new continuity(db);
	sensor * sens		= new sensor(db);
	tamper * tamp		= new tamper(db);
	presence * pres		= new presence(db);

	//User->setUserByIdCard("1477334037");

	//cont->selectStatut();
	//qDebug() << "--------------------------";
	//sens->selectStatut();
	//qDebug() << "--------------------------";
	//tamp->selectStatut();
	//qDebug() << "--------------------------";
	//pres->selectStatut();

    return a.exec();
}