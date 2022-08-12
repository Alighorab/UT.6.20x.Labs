#define RAND_MAX ((1U << 31) - 1)


void Seed(int x);
int Rand(void);
int SRand(int s);
void Delay(unsigned long count);
