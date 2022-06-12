#include "SendUserResultOperation.h"

/* Constructor SendUserResultOperation class */
SendUserResultOperation::SendUserResultOperation(QWebSocket * ws, QString result)
{
	this->ws = ws;
	this->result = result;
}

/* Run SendUserResultOperation thread */
void SendUserResultOperation::run()
{
	// Send user informations on client
	ws->sendTextMessage("getUser;" + result);
}

/* Process when the thread is done */
void SendUserResultOperation::onOperationDone()
{
}
