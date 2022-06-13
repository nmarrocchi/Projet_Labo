#include "SendAuthResultOperation.h"

/* Constructor SendAuthResultOperation class */
SendAuthResultOperation::SendAuthResultOperation(QWebSocket * ws, int result, int isAdmin)
{
	this->ws = ws;
	this->result = result;
	this->isAdmin = isAdmin;
}

/* Run SendAuthResultOperation thread */
void SendAuthResultOperation::run()
{
	// Send result on client
	ws->sendTextMessage("Auth;" + QString::number(result) + ";" + QString::number(isAdmin));
}

/* Process when the thread is done */
void SendAuthResultOperation::onOperationDone()
{
}
