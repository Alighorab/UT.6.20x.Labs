#include "Random.h"

int rseed = 0;
 
void
Seed(int x)
{
	rseed = x;
}
 
int
Rand(void)
{
	return rseed = (rseed * 1103515245 + 12345) & RAND_MAX;
}

int
SRand(int s)
{
    Seed(s);
    return Rand();
}

void
Delay(unsigned long count) 
{
    unsigned long volatile time;
    while (count > 0) {
        time = 727240;
        while (time) {
            time--;
        }
        count--;
    }
}
