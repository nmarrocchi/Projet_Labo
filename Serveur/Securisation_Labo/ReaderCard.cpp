#include "ReaderCard.h"

ReaderCard * ReaderCard::instance = NULL;

ReaderCard * ReaderCard::getInstance()
{
	if (instance == NULL)
	{
		instance = new ReaderCard();
	}

	return instance;
}

ReaderCard::ReaderCard() {

	if (ReaderOpen() != 0) {
	
		printf("Erreur, le lecteur n a pas pu etre ouvert");
		exit(-1);
	
	}
	printf("Lecteur ouvert");
	
	GetReaderType(&readerType);
	ReaderUISignal(3, 3);

	run();

}

void ReaderCard::run()
{
	ReaderCard::read();
}

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

		printf("%s \n",Card["cardSerial"].toString());

	cardType = NULL;
	cardSerial = NULL;
	Card.clear();

}

void ReaderCard::write(QString newContent) {
	unsigned char	ucKeyIndex = 0,
		ucAuthMode = MIFARE_AUTHENT1A;
	
	unsigned short	usLinearAddress = 0,
		usDataLength = 10,
		usBytesRet = 10;
	
	QByteArray test = newContent.toLatin1();
	
	unsigned char *res = (unsigned char *)strdup(test.constData());
	
	
	LinearWrite(res, usLinearAddress, usDataLength, &usBytesRet, ucAuthMode, ucKeyIndex);
	ReaderCard::read();
}