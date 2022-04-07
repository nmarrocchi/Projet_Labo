#include "RFID.h"

RFID::RFID(QObject *parent) : QObject(parent) {

	if (ReaderOpen() != 0) {
	
		qDebug() << "Erreur, le lecteur n a pas pu etre ouvert";
		exit(-1);
	
	}
	qDebug() << "Lecteur ouvert";
	
	GetReaderType(&readerType);
	ReaderUISignal(3, 3);

}

void RFID::read() {

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

	if (lastCardRead != Card["cardSerial"].toString())
	{
		qDebug() << Card["cardSerial"].toString() << endl;
		lastCardRead = Card["cardSerial"].toString();
		//User->setUserByIdCard("1477334037");
		//User->setUserByIdCard(cardID);
	}
	
	cardType = NULL;
	cardSerial = NULL;
	Card.clear();

}

void RFID::write(QString newContent) {
	unsigned char	ucKeyIndex = 0,
		ucAuthMode = MIFARE_AUTHENT1A;
	
	unsigned short	usLinearAddress = 0,
		usDataLength = 10,
		usBytesRet = 10;
	
	QByteArray test = newContent.toLatin1();
	
	unsigned char *res = (unsigned char *)strdup(test.constData());
	
	
	LinearWrite(res, usLinearAddress, usDataLength, &usBytesRet, ucAuthMode, ucKeyIndex);
	RFID::read();
}

RFID::~RFID() {


}
