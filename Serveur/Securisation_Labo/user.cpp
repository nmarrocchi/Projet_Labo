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
	QSqlQuery getUsercount;
	getUsercount.prepare("SELECT COUNT(*) FROM " + BDD::user_table + " WHERE idCard = '" + idCard + "'");

	if (getUsercount.exec())
	{
		getUsercount.next();

		if (getUsercount.value(0).toInt())
		{
			qDebug() << "User Exist\n" << endl;
			//qDebug() << BDD::selectdb(BDD::user_table, " WHERE idCard = " + idCard) << endl;
		}
		else { qDebug() << "User not Exist\n" << endl; }
	}

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
