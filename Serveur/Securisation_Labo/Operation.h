#pragma once
class Operation
{
private:
	/* Run Operation thread */
	virtual void run() = 0;

	/* Process when the thread is done */
	virtual void onOperationDone() = 0;

public:
	/* Process when a task is add on child class */
	void runTask();
};

