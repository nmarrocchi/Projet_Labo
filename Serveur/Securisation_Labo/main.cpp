#include <QtCore/QCoreApplication>

#include "database.h"
#include "user.h"
#include "security.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	database *db = new database();
	user * User = new user();
	continuity * cont = new continuity(db);

	User->setUserByIdCard("1");
	cont->selectStatut();

    return a.exec();
}