#include "user.h"

user::user()
{}

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

// - get user infos by idCard
void user::setUserByIdCard(QString idCard)
{
	qDebug() << "SELECT COUNT(*) FROM user WHERE idCard = " + idCard << endl;
	int countUser = database::countdb(database::user_table, " WHERE idCard = " + idCard);
	qDebug() << countUser << endl;
	//if (countUser > 0)
	//{
	//	qDebug() << "User Exist\n" << endl;
	//	QString * User[4];
	//	*User = database::selectdb(database::user_table, " WHERE idCard = " + idCard);
	//}
	//else { 
	//	qDebug() << "User not Exist\n" << endl; 
	//}
}

void user::getIdCard(QString user)
{}

void user::getMail(QString user)
{}

void user::getAdmin(QString user)
{}

void user::connexion()
{}

void user::deconnexion()
{}

void user::selectUser(QString user)
{}

void user::insertUser(QString user)
{}

void user::updateUser(QString user)
{}

void user::deleteUser(QString user)
{}

void user::histoPassage()
{}

void user::histoPassageByUser()
{}


/* Récupération heure

// date / heure actuelle basée sur le système actuel
			time_t tmm = time(0);

			// convertir en forme de chaîne
			char* dt = ctime(&tmm);
			qDebug() << "La date et l'heure locales sont: " << dt << endl;

*/
