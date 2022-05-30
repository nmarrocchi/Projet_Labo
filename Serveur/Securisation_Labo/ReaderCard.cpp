#include "ReaderCard.h"
#include <qdebug.h>

// - Set securitySystem Instance to NULL
ReaderCard * ReaderCard::instance = NULL;

// - Create ReaderCard Instance
ReaderCard * ReaderCard::getInstance(database * db)
{
	if (instance == NULL)
	{
		instance = new ReaderCard(db);
	}

	return instance;
}

// - Open Reader & loop read function
ReaderCard::ReaderCard(database * db) {

	_user = new user(db);
	_db = db;
	if (ReaderOpen() != 0) {
	
		printf("Erreur, le lecteur n a pas pu etre ouvert \n");
		exit(-1);
	
	}
	printf("Lecteur ouvert \n");
	
	GetReaderType(&readerType);
	ReaderUISignal(3, 3);

	run();

}

// - run ReaderCard loop
void ReaderCard::run()
{
	while (1)
	{
		ReaderCard::read();
	}
}

// - Read Card
void ReaderCard::read() {

	QString lastCardRead = "";
	QMap< QString, QVariant > Card;

	Card["isset"] = false;

	if (GetDlogicCardType(&cardType))
		return emit hasRead(Card);

	GetCardId(&cardType, &cardSerial);

	Card["cardType"] = cardType;
	Card["cardSerial"] = cardSerial;

	if (cardType == DL_MIFARE_CLASSIC_1K)
		return emit hasRead(Card);

	Card["isset"] = true;

	unsigned char	ucKeyIndex = 0,
		ucAuthMode = MIFARE_AUTHENT1A;

	unsigned short	usLinearAddress = 0,
		usDataLength = 20,
		usBytesRet = 0;

	unsigned char  *pData = 0;

	pData = new unsigned char[usDataLength];
	LinearRead(pData, usLinearAddress, usDataLength, &usBytesRet, ucAuthMode, ucKeyIndex);

	Card["data"] = (char*)pData;

	emit hasRead(Card);

	QString CardIdDetected = Card["cardSerial"].toString();
	// - Card Verification

	_user->setUserByIdCard(CardIdDetected); // Check la validité de la carte
	
	
	cardType = NULL;
	cardSerial = NULL;
	Card.clear();

	sleep(2);

}
