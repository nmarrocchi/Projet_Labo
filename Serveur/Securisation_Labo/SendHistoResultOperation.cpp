#include "SendHistoResultOperation.h"

SendHistoResultOperation::SendHistoResultOperation(QWebSocket * ws, QString result)
{
	this->ws = ws;
	this->result = result;
}

void SendHistoResultOperation::run()
{
	ws->sendTextMessage("HistoSystem;" + result);
}

void SendHistoResultOperation::onOperationDone()
{
}
