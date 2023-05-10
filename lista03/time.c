#include <stdlib.h>
#include <time.h>

#pragma once
double get_time(void)
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec + now.tv_nsec*1e-9;
}
