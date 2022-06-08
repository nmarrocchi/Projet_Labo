#include <QtCore/QCoreApplication>

#include "ReaderCard.h"
#include "webServer.h"
#include "database.h"
#include "timeSlot.h"
#include "security.h"
#include "continuity.h"
#include "sensor.h"
#include "tamper.h"
#include "presence.h"
#include "securitySysteme.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	security::superviseTable(); // Affiche un tableau pour les états des capteurs

	//database * db = new database();

	webServer::getInstance(2569); // Instancie le serveur websocket
	
	//ReaderCard::getInstance(db);	// Instancie le lecteur RFID

	securitySysteme::getInstance();	// Affiche les états des capteurs

    return a.exec();
}