/* Sound.h */
/* Runs on TM4C123 or LM4F120 */
/* Prototypes for basic functions to play sounds from the */
/* original Space Invaders. */
/* Jonathan Valvano */
/* November 19, 2012 */

#define Sound_Shoot()           Sound_Play(shoot, 4080);
#define Sound_Killed()          Sound_Play(invaderkilled, 3377);
#define Sound_Explosion()       Sound_Play(explosion, 2000);
#define Sound_Fastinvader1()    Sound_Play(fastinvader1, 982);
#define Sound_Fastinvader2()    Sound_Play(fastinvader2, 1042);
#define Sound_Fastinvader3()    Sound_Play(fastinvader3, 1054);
#define Sound_Fastinvader4()    Sound_Play(fastinvader4, 1098);
#define Sound_Highpitch()       Sound_Play(highpitch, 1802);

void Sound_Init(void);
void Sound_Play(const unsigned char *pt, unsigned long count);

