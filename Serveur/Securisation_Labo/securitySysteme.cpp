#include "securitySysteme.h"
#include "continuity.h"
#include "sensor.h"
#include "tamper.h"
#include "presence.h"

// - Set securitySystem Instance to NULL
securitySysteme * securitySysteme::instance = NULL;

// - Create securitySystem Instance
securitySysteme * securitySysteme::getInstance(database * db)
{
	if (instance == NULL)
	{
		instance = new securitySysteme(db);
	}

	return instance;
}

// - Instance All Sensors Class
securitySysteme::securitySysteme(database * db)
{
	PCI_7248_Card * card = new PCI_7248_Card();
	secDevices.push_back(new continuity(card, db));
	secDevices.push_back(new sensor(card, db));
	secDevices.push_back(new tamper(card, db));
	secDevices.push_back(new presence(card, db));

	start();
}

// - Run securitySystem loop
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