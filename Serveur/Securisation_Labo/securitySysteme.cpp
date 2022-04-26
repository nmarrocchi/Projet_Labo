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
	PCI_7248_Card * card = new PCI_7248_Card();
	secDevices.push_back(new continuity(card, db));
	secDevices.push_back(new sensor(card, db));
	secDevices.push_back(new tamper(card, db));
	secDevices.push_back(new presence(card, db));

	ConsoleTable ct(BASIC);
	ct.setPadding(1);

	ct.addColumn("Country");
	ct.addColumn("Name");
	ct.addColumn("Profession");
	ct.addColumn("Age");

	auto entry = new ConsoleTableRow(4);
	entry->addEntry("Germany", 0);
	entry->addEntry("Michael", 1);
	entry->addEntry("Computer Engineer", 2);
	entry->addEntry("19", 3);
	ct.addRow(entry);

	ct.addRow(entry);

	// Print all entries
	ct.printTable();

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