
#include <qobject.h>
#include <qdebug.h>
#include "database.h"

class user
{

private:
	database * _db;
	int _idCard;
	QString _mail;
	QString _password;
	bool _isAdmin;

public slots:
	user(database * db);
	~user();

	// - Set user variables with user infos
	void setUser(QString idCard, QString mail, QString password, QString isAdmin);

	// - Get all informations of user by CardID
	void setUserByIdCard(QString idCard);

	// - Get card id from specific user
	void getIdCard(QString user);

	// - Get user mail value
	void getMail(QString user);

	// - Get user admin value
	void getAdmin(QString user);

	// - Select user from database
	void selectUser(QString user);

	// - Insert user from database
	void insertUser(QString user);

	// - Update user from database
	void updateUser(QString user);

	// - Delete user from database
	void deleteUser(QString user);

	// - Get all passage
	void histoPassage();

	// - Get all passage from specific user
	void histoPassageByUser();

};

