#include "CheckRFIDUserOperation.h"
#include "database.h"
#include "securitySysteme.h"

/* Constructor CheckRFIDUserOperation class */
CheckRFIDUserOperation::CheckRFIDUserOperation(QString idCard)
{
	this->idCard = idCard;
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
		}
		else {
			// Verification if the time slot is valid
			if (timeSlot::validateTime() == true)
			{
				accessAuthorized = true;

				// Insert the passage on database
				query.exec("INSERT INTO `passage`(`idCard`) VALUES (" + idCard + ")");
			}
		}
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
