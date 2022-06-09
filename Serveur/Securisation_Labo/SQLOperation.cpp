#include "Operation.h"

void Operation::runTask()
{
	run();
	onOperationDone();
	delete this;
}
