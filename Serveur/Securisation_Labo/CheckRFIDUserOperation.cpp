#include "CheckRFIDUserOperation.h"
#include "database.h"
#include "securitySysteme.h"

CheckRFIDUserOperation::CheckRFIDUserOperation(QString idCard)
{
	this->idCard = idCard;
	accessAuthorized = false;
}

void CheckRFIDUserOperation::run()
{
	database * _db = database::getInstance();
	int countUser = _db->countdb(_db->user_table, " WHERE idCard = " + idCard);
	if (countUser > 0)
	{
		QSqlQuery query; 
		query = _db->selectdb(_db->user_table, " WHERE idCard = " + idCard);

		query.next();

		bool isAdmin = query.value(3).toInt();

		if (isAdmin == 1) 
		{
			accessAuthorized = true;
			query.exec("INSERT INTO `passage`(`idCard`) VALUES (" + idCard + ")");
		}
		else {
			if (timeSlot::validateTime() == true)
			{
				accessAuthorized = true;
				query.exec("INSERT INTO `passage`(`idCard`) VALUES (" + idCard + ")");
			}
		}
	}
	else {
		qDebug() << "Carte non renseignee en base de donnee\n" << endl;
	}
}

void CheckRFIDUserOperation::onOperationDone()
{
	if (accessAuthorized)
	{
		// Ouvrir 
		LockOpeningThread * thread = new LockOpeningThread();
		thread->start();
	}
}

void LockOpeningThread::run()
{
	securitySysteme::getInstance()->getCard()->writeCard(Channel_P2B, 2, 0);
	QThread::msleep(5000);
	securitySysteme::getInstance()->getCard()->writeCard(Channel_P2B, 2, 1);
	deleteLater();
}
