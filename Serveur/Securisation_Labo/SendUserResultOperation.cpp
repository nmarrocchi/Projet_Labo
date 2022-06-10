#include "SendUserResultOperation.h"

SendUserResultOperation::SendUserResultOperation(QWebSocket * ws, QString result)
{
	this->ws = ws;
	this->result = result;
}

void SendUserResultOperation::run()
{
	ws->sendTextMessage("getUser;" + result);
}

void SendUserResultOperation::onOperationDone()
{
}
