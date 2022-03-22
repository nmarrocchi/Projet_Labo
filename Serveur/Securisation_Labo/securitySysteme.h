#pragma once

#include <qthread.h>

class securitySysteme : public QThread
{
	Q_OBJECT
		void run() override {
		QString result;
		emit resultReady(result);
	}
signals:
	void resultReady(const QString &s);
};

