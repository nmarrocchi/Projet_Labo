#pragma once
class Operation
{
private:
	virtual void run() = 0;
	virtual void onOperationDone() = 0;

public:
	void runTask();
};

