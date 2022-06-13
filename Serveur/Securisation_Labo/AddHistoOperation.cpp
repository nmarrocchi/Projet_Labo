#include "AddHistoOperation.h"

/* Constructor AddHistoOperation class */
AddHistoOperation::AddHistoOperation(int value, bool statut)
{
	this->value = value;
	this->statut = statut;
}

/* Run AddHistoOperation thread */
void AddHistoOperation::run()
{
	// Insert values in historical in database
	QSqlQuery query;
	query.exec("INSERT INTO `historical`(`idSecurity`, `statut`) VALUES (" + QString::number(value) + ", " + QString::number(statut) + ")");
}

/* Process when the thread is done */
void AddHistoOperation::onOperationDone()
{
}
