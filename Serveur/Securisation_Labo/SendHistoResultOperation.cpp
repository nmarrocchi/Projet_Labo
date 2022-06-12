#include "SendHistoResultOperation.h"

/* Constructor SendHistoResultOperation class */
SendHistoResultOperation::SendHistoResultOperation(QWebSocket * ws, QString result)
{
	this->ws = ws;
	this->result = result;
}

/* Run SendHistoResultOperation thread */
void SendHistoResultOperation::run()
{
	// Send historical on client
	ws->sendTextMessage("HistoSystem;" + result);
}

/* Process when the thread is done */
void SendHistoResultOperation::onOperationDone()
{
}
