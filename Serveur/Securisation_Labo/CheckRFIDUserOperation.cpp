#include "CheckRFIDUserOperation.h"
#include "database.h"
#include "securitySysteme.h"
#include "SendRFIDUserOperation.h"

/* Constructor CheckRFIDUserOperation class */
CheckRFIDUserOperation::CheckRFIDUserOperation(QString idCard)
{
	this->idCard = idCard;

	this->webserver = webServer::getInstance();

	accessAuthorized = false;
}

/* Run CheckRFIDUserOperation thread */
void CheckRFIDUserOperation::run()
{
	database * _db = database::getInstance();

	// Verification if the RFID Card exist in database
	int countUser = _db->countdb(_db->user_table, " WHERE idCard = " + idCard);

	if (countUser > 0)
	{
		// Verification if the user is an administrator
		QSqlQuery query; 
		query = _db->selectdb(_db->user_table, " WHERE idCard = " + idCard);

		query.next();

		bool isAdmin = query.value(3).toInt();

		if (isAdmin == 1) 
		{
			accessAuthorized = true;

			// Insert the passage on database
			query.exec("INSERT INTO `passage`(`idCard`) VALUES (" + idCard + ")");

			actualiseHisto();
		}
		else {
			// Verification if the time slot is valid
			if (timeSlot::validateTime() == true)
			{
				accessAuthorized = true;

				// Insert the passage on database
				query.exec("INSERT INTO `passage`(`idCard`) VALUES (" + idCard + ")");

				actualiseHisto();
			}
		}
	}
}

/* Update values on historical on client */
void CheckRFIDUserOperation::actualiseHisto()
{
	QSqlQuery query;

	// Select all values on historical table in database
	query.exec("SELECT passage.idCard, user.mail, DATE_FORMAT(passage.date, '%d/%c/%Y %T') FROM `passage`, `user` WHERE passage.idCard = user.idCard ORDER BY date DESC");

	if (query.next())
	{
		idCard		= query.value(0).toString();
		mailValue	= query.value(1).toString();
		dateValue	= query.value(2).toString();

		QString result = "Passage;" + idCard + ";" + mailValue + ";" + dateValue;

		// Send result values on SendHistoResultOperation class
		webServer::getInstance()->addOperation(new SendRFIDUserOperation(webserver, result));
	}
}

/* Process when the thread is done */
void CheckRFIDUserOperation::onOperationDone()
{
	// Verification if access is valid
	if (accessAuthorized == true)
	{
		LockOpeningThread * thread = new LockOpeningThread();
		thread->start();
	}
}

/* Run LockOpeningThread thread */
void LockOpeningThread::run()
{
	// Active lock with PCI_7248_Card class
	securitySysteme::getInstance()->getCard()->writeCard(Channel_P2B, 2, 0);

	QThread::msleep(5000);

	// Desactive lock with PCI_7248_Card class
	securitySysteme::getInstance()->getCard()->writeCard(Channel_P2B, 2, 1);

	deleteLater();
}
