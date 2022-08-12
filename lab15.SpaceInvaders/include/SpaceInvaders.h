#include "Nokia5110.h"
#include "Sound.h"
#include "tm4c123gh6pm.h"
#include "SysTick.h"
#include "ADC.h"
#include "weapones.h"
#include "PLL.h"
#include "Random.h"

#define ALIVE 1
#define DEAD  0

#define MAX_ENEMIES 4
#define MAX_PMISSILES 20
#define MAX_EMISSILES 10
#define MAX_SMISSILES 2

#define HALF_SECOND 15
#define ONE_SECOND  30

typedef struct Ship {
    unsigned long x;
    unsigned long y;
    const unsigned char *image;
    long life;
} Ship;

typedef struct Enemy {
    unsigned long x;
    unsigned long y;
    const unsigned char *image[2];
    unsigned long frame;
    long life;
} Enemy;

typedef struct Buncker {
    unsigned long x;
    unsigned long y;
    const unsigned char *image[4];
    unsigned long frame;
} Buncker;

typedef struct Missile {
    unsigned long x;
    unsigned long y;
    const unsigned char *image[3];
    unsigned long frame;
    long life;
} Missile;


void DisableInterrupts(void);
void EnableInterrupts(void);
void Game_Init(void);
void Game_CreateObjects(void);
void Game_DrawObjects(void);
void Game_Loop(void);
void Game_Engine(void);
void Game_Update(void);
unsigned long Game_GetShipPosition(void);
void Game_FireMissile(int player);
void Game_FireSpecialMissile(int player);
void Game_MoveMissiles(void);
void Game_CatchEnemy(void);
void Game_CatchPlayer(void);
void Game_Over(void);
void Game_Win(void);
