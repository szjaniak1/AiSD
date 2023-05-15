#include <stdlib.h>
#include <time.h>

#pragma once
int get_time(void)
{
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec * 1000000000 + now.tv_nsec * 1000;
}
