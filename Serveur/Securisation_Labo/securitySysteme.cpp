#include "securitySysteme.h"
#include "continuity.h"
#include "sensor.h"
#include "tamper.h"
#include "presence.h"

securitySysteme * securitySysteme::instance = NULL;

securitySysteme * securitySysteme::getInstance()
{
	if (instance == NULL)
	{
		instance = new securitySysteme();
	}

	return instance;
}


securitySysteme::securitySysteme()
{
	db = new database();
	PCI_7248_Card * card = new PCI_7248_Card();
	secDevices.push_back(new continuity(card, db));
	secDevices.push_back(new sensor(card, db));
	secDevices.push_back(new tamper(card, db));
	secDevices.push_back(new presence(card, db));

	run();
}


void securitySysteme::run()
{
	while (1)
	{
		for (int i = 0; i < secDevices.size(); i++)
		{
			secDevices[i]->selectStatut();
		}

		QThread::sleep(1);
	}
}