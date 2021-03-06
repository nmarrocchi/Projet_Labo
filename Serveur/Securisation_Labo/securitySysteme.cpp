#include "securitySysteme.h"
#include "continuity.h"
#include "sensor.h"
#include "tamper.h"
#include "presence.h"
#include "SystemData.h"
#include "webServer.h"

// - Set securitySystem Instance to NULL
securitySysteme * securitySysteme::instance = NULL;

// - Create securitySystem Instance
securitySysteme * securitySysteme::getInstance()
{
	if (instance == NULL)
	{
		instance = new securitySysteme();
	}

	return instance;
}

PCI_7248_Card * securitySysteme::getCard()
{
	return card;
}

// - Instance All Sensors Class
securitySysteme::securitySysteme()
{
	start();
}

// - Run securitySystem loop
void securitySysteme::run()
{
	card = new PCI_7248_Card();
	database * db = database::getInstance();

	timeSlot::getInstance(NULL, NULL);

	secDevices.push_back(new continuity(card, db));
	secDevices.push_back(new sensor(card, db));
	secDevices.push_back(new tamper(card, db));
	secDevices.push_back(new presence(card, db));

	while (1)
	{
		timeSlot::changeRegularTime();

		QList<bool> tamperStates;
		QList<bool> continuityStates;
		QList<bool> presenceStates;
		QList<bool> sensorStates;

		for (int i = 0; i < secDevices.size(); i++)
		{
			QList<bool> states = secDevices[i]->selectStatut();

			if (dynamic_cast<continuity*>(secDevices[i]) != NULL)
			{
				continuityStates = states;
			}
			else if (dynamic_cast<sensor*>(secDevices[i]) != NULL)
			{
				sensorStates = states;
			}
			else if (dynamic_cast<tamper*>(secDevices[i]) != NULL)
			{
				tamperStates = states;
			}
			else if (dynamic_cast<presence*>(secDevices[i]) != NULL)
			{
				presenceStates = states;
			}
		}

		SystemData data;
		data.setData(continuityStates, sensorStates, tamperStates, presenceStates);
		webServer::getInstance()->updateSystemData(data);

		QThread::sleep(1);
	}
}