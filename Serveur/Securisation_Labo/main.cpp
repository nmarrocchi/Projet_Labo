#include <QtCore/QCoreApplication>

#include "user.h"
#include "database.h"
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

	database * db = new database();
	user * User = new user(db);

	//Server * server = new Server();

	User->setUserByIdCard("1063727088"); // Check la validité de la carte

	securitySysteme::getInstance(db);	// Affiche les états des capteurs

    return a.exec();
}