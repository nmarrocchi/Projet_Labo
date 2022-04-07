
#include <qobject.h>
#include <qdebug.h>

#include "database.h"

class user : database
{

private:
	int _idCard;
	QString _mail;
	QString _password;
	bool _isAdmin;

public slots:
	user();
	~user();

	void setUser(QString idCard, QString mail, QString password, QString isAdmin);
	void setUserByIdCard(QString idCard);
	void getIdCard(QString user);
	void getMail(QString user);
	void getAdmin(QString user);
	void connexion();
	void deconnexion();
	void selectUser(QString user);
	void insertUser(QString user);
	void updateUser(QString user);
	void deleteUser(QString user);
	void histoPassage();
	void histoPassageByUser();

};

