#include <QtCore/QCoreApplication>

#include "BDD.h"
#include "user.h"
#include "security.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	BDD *db = new BDD();

	security security(db);

    return a.exec();
}