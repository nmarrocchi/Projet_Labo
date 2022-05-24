#include "user.h"

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
	qDebug() << "//----- Verification Carte -----//\n" << endl;
	qDebug() << "Passage de le carte " + idCard << endl;
	int countUser = _db->countdb(_db->user_table, " WHERE idCard = " + idCard);
	if (countUser > 0)
	{
		QString * User[4];
	
		//*User = database::selectdb(database::user_table, " WHERE idCard = " + idCard);
		//
		//_idCard = User[1]->toInt();
		//_mail = User[2]->toStdString;
		//_password = User[3]->toStdString;
		//_isAdmin = User[4]->toInt();

		_isAdmin = 1;
	
		if (_isAdmin == 1) {
			qDebug() << "L'utilisateur est administrateur" << endl;
			qDebug() << "Acces accorde, ouverture de la gache" << endl;
			//Ouverture de la gâche
		}
		else {
			qDebug() << "Verification de la plage horaire..." << endl;
			// Vérification de la plage horaire
			qDebug() << "Acces en plage horaire, acces accorde" << endl;
			qDebug() << "ouverture de la gache" << endl;
			// Si plage horaire respectée alors ouverture de la gâche
		}
	}
	else { 
		qDebug() << "Carte non renseignee en base de donnee\n" << endl; 
	}
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
