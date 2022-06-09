#include "user.h"
#include "CheckRFIDUserOperation.h"

user::user(database * db)
{
	_db = db;
}

user::~user()
{}

// - Set user variables with user infos
void user::setUser(QString idCard, QString mail, QString password, QString isAdmin)
{
	this->_idCard = idCard.toInt();
	this->_mail = mail;
	this->_password = password;
	this->_isAdmin = isAdmin.toInt();
}

// - get all informations of user by CardID
void user::setUserByIdCard(QString idCard)
{
	database::getInstance()->addOperation(new CheckRFIDUserOperation(idCard));
}

// - Get card id from specific user
void user::getIdCard(QString user)
{}

// - Get user mail value
void user::getMail(QString user)
{}

// - Get user admin value
void user::getAdmin(QString user)
{}

// - Select user from database
void user::selectUser(QString user)
{}

// - Insert user from database
void user::insertUser(QString user)
{}

// - Update user from database
void user::updateUser(QString user)
{}

// - Delete user from database
void user::deleteUser(QString user)
{}

// - Get all passage
void user::histoPassage()
{}

// - Get all passage from specific user
void user::histoPassageByUser()
{}


/* Récupération heure

// date / heure actuelle basée sur le système actuel
			time_t tmm = time(0);

			// convertir en forme de chaîne
			char* dt = ctime(&tmm);
			qDebug() << "La date et l'heure locales sont: " << dt << endl;

*/
