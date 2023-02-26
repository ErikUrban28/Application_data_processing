#include <iostream>

#include "handler.h"
#include "structures/heap_monitor.h"
#include "structures/list/array_list.h"

int main()
{
	initHeapMonitor();
	Handler handler;
	try {
		handler.spusti();
	} catch (std::runtime_error& erorr)
	{
		std::cout << erorr.what();
		return 1;
	}
}





