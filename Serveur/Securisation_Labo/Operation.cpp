#include "Operation.h"

/* Process when a task is add on child class */
void Operation::runTask()
{
	run();
	onOperationDone();
	delete this;
}
