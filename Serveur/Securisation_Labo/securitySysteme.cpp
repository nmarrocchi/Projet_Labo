#include "securitySysteme.h"
#include "continuity.h"
#include "sensor.h"
#include "tamper.h"
#include "presence.h"

securitySysteme * securitySysteme::instance = NULL;

securitySysteme * securitySysteme::getInstance()
{
	if (instance == NULL)
		instance = new securitySysteme();

	return instance;
}


securitySysteme::securitySysteme()
{
	db = new database();
	secDevices.push_back(new continuity(db));
	secDevices.push_back(new sensor(db));
	secDevices.push_back(new tamper(db));
	secDevices.push_back(new presence(db));
	run();
}


void securitySysteme::run()
{
	while (1)
	{
		for (int i = 0; i < secDevices.size(); i++)
		{
			secDevices[i]->selectStatut();
			qDebug() << "----------------------------------------------------";
		}

		qDebug() << "=====================================================";

		QThread::sleep(5);
	}
}