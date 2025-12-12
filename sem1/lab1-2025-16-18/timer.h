#include <sys/time.h>

#define TIMER(program) \
timeval start, end; \
gettimeofday(&start, NULL); \
program \
gettimeofday(&end, NULL);\
cout << "Time: " << end.tv_usec - start.tv_usec << " nanoseconds\n";