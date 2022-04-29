#include <QtCore/QCoreApplication>

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

	//user * User = new user();
	//Server * server = new Server();

	//User->setUserByIdCard("1477334037");

	security::superviseTable();

	securitySysteme::getInstance();

    return a.exec();
}