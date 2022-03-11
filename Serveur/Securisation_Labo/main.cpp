#include <QtCore/QCoreApplication>

#include "database.h"
#include "user.h"
#include "security.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	database *db = new database();
	user * User = new user();

	User->setUserByIdCard("1");

	//security security(db);

    return a.exec();
}