#include "SendAddHistoOperation.h"

SendAddHistoOperation::SendAddHistoOperation(webServer * webserver, QString result)
{
	this->webserver = webserver;
	this->result = result;
}

void SendAddHistoOperation::run()
{
	// Send result values on all clients connected
	for (QList<QWebSocket*>::iterator it = webserver->wsclients.begin(); it != webserver->wsclients.end(); it++) {
		(*it)->sendTextMessage("AddHisto;" + result);
	}
}

void SendAddHistoOperation::onOperationDone()
{
}
