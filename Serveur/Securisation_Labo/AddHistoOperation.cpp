#include "AddHistoOperation.h"

AddHistoOperation::AddHistoOperation(int value, bool statut)
{
	this->value = value;
	this->statut = statut;
}

void AddHistoOperation::run()
{
	QSqlQuery query;
	query.exec("INSERT INTO `historical`(`idSecurity`, `statut`) VALUES (" + QString::number(value) + ", " + QString::number(statut) + ")");
}

void AddHistoOperation::onOperationDone()
{
}
