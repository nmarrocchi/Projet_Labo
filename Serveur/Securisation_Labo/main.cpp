#include <QtCore/QCoreApplication>

#include "ConfigData.h"
#include "ReaderCard.h"
#include "webServer.h"
#include "securitySysteme.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	// - Create ConfigData Instance
	ConfigData * config = ConfigData::getInstance();

	// - Create the supervise table
	security::superviseTable();

	// - Create webServer Instance
	webServer::getInstance(config->getPort());
	
	// - Create ReaderCard Instance
	ReaderCard::getInstance();

	// - Create securitySysteme Instance
	securitySysteme::getInstance();

    return a.exec();
}