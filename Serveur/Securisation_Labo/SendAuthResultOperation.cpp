#include "SendAuthResultOperation.h"

SendAuthResultOperation::SendAuthResultOperation(QWebSocket * ws, int result)
{
	this->ws = ws;
	this->result = result;
}

void SendAuthResultOperation::run()
{
	// Send result on client
	ws->sendTextMessage("Auth;" + QString::number(result));
}

void SendAuthResultOperation::onOperationDone()
{
}
