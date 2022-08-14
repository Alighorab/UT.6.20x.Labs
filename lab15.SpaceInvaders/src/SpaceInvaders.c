#include "SpaceInvaders.h"
#include "images.h"

Ship playerShip;
Enemy enemy[MAX_ENEMIES];
Bunker bunker[MAX_BUNKERS];
Missile playerMissile[MAX_PMISSILES];
Missile enemyMissile[MAX_EMISSILES];
Missile enemySpecialMissile[MAX_SMISSILES];
Missile playerSpecialMissile[MAX_SMISSILES];
unsigned long Update = 0;

int
main(void)
{
    Game_Init();
    Game_Loop();
}

void
Game_Init(void)
{
    PLL_Init();
    Nokia5110_Init();
    SysTick_Init(Game_Engine);
    Sound_Init();
    ADC0_Init();
    Weapones_Init();
    EnableInterrupts();

    Game_CreateObjects();
    Game_DrawObjects();
}

void
Game_CreateObjects(void)
{
    int i, newX, newY, offset = 3;
    const unsigned char *frameA[MAX_ENEMIES] = {
        SmallEnemy10PointA, SmallEnemy20PointA, SmallEnemy30PointA};
    const unsigned char *frameB[MAX_ENEMIES] = {
        SmallEnemy10PointB, SmallEnemy20PointB, SmallEnemy30PointB};

    playerShip.x = Game_GetShipPosition();
    playerShip.y = SCREENH;
    playerShip.image = PlayerShip0;
    playerShip.life = ALIVE;

    newX = 0;
    newY = 10;
    for (i = 0; i < MAX_ENEMIES; i++) {
        enemy[i].x = newX;
        enemy[i].y = newY;
        enemy[i].image[0] = frameA[i % 3];
        enemy[i].image[1] = frameB[i % 3];
        enemy[i].life = ALIVE;
        newX += 20;
        if (i == 3) {
            newX = offset;
            newY += 15;
        }
    }

    for (i = 0; i < MAX_BUNKERS; i++) {
        bunker[i].x = 5 + (28 * i);
        bunker[i].y = 37;
        bunker[i].image[0] = Bunker0;
        bunker[i].image[1] = Bunker1;
        bunker[i].image[2] = Bunker2;
        bunker[i].image[3] = Bunker3;
        bunker[i].frame = 0;
        bunker[i].life = ALIVE;
    }

    for (i = 0; i < MAX_PMISSILES; i++) {
        playerMissile[i].image[0] = Missile0;
        playerMissile[i].life = DEAD;
    }

    for (i = 0; i < MAX_EMISSILES; i++) {
        enemyMissile[i].image[0] = Missile0;
        enemyMissile[i].life = DEAD;
    }

    for (i = 0; i < MAX_SMISSILES; i++) {
        enemySpecialMissile[i].image[0] = 
            playerSpecialMissile[i].image[0] = Missile0;
        enemySpecialMissile[i].life = playerSpecialMissile[i].life = DEAD;
    }
}

void
Game_DrawObjects(void)
{
    int i;
    Nokia5110_ClearBuffer();
    Nokia5110_PrintBMP(playerShip.x, playerShip.y, playerShip.image, 0);
    for (i = 0; i < MAX_ENEMIES; i++) {
        Nokia5110_PrintBMP(enemy[i].x, enemy[i].y, 
                    enemy[i].image[enemy[i].frame], 0);
    }
    for (i = 0; i < MAX_BUNKERS; i++) {
        Nokia5110_PrintBMP(bunker[i].x, bunker[i].y, 
                    bunker[i].image[bunker[i].frame], 0);
    }
    Nokia5110_DisplayBuffer();
}

void
Game_Loop(void)
{
    while (1) {
        if (Update == 1) {
            Game_Update();
            Update = 0;
        }
    }
}

void
Game_Engine(void)
{
    static int fire = 0, specialFire = 0;

    playerShip.x = Game_GetShipPosition();
    Game_CatchEnemy();
    Game_CatchPlayer();
    Game_CatchBunker();
    Game_MoveMissiles();

    if (Weapones_GetButtons() == FIRE) {
        Game_FireMissile(1);
    }

    if (Weapones_GetButtons() == SPECIAL_FIRE) {
        Game_FireSpecialMissile(1);
    }
    
    if (fire++ == HALF_SECOND/2) {
        fire = 0;
        Game_FireMissile(0);
    }

    if (specialFire++ == (2 * ONE_SECOND)) {
        specialFire = 0;
        Game_FireSpecialMissile(0);
    }

    Update = 1;
}

void
Game_Update(void)
{
    int i, j = 0;
    Nokia5110_ClearBuffer();

    if (playerShip.life == ALIVE) {
        Nokia5110_PrintBMP(playerShip.x, playerShip.y, playerShip.image, 0);
    } else {
        Nokia5110_PrintBMP(playerShip.x, playerShip.y, SmallExplosion0, 0);
    }

    for (i = 0; i < MAX_ENEMIES; i++) {
        if (enemy[i].life == ALIVE) {
            Nokia5110_PrintBMP(enemy[i].x, enemy[i].y, enemy[i].image[enemy[i].frame], 0);
            j++;
        }
    }
        
    for (i = 0; i < MAX_PMISSILES; i++) {
        if (playerMissile[i].life == ALIVE) {
            Nokia5110_PrintBMP(playerMissile[i].x, playerMissile[i].y,
                    playerMissile[i].image[playerMissile[i].frame], 0);
        }
    }

    for (i = 0; i < MAX_EMISSILES; i++) {
        if (enemyMissile[i].life == ALIVE) {
            Nokia5110_PrintBMP(enemyMissile[i].x, enemyMissile[i].y,
                    enemyMissile[i].image[enemyMissile[i].frame], 0);
        }
    }

    for (i = 0; i < MAX_SMISSILES; i++) {
        if (enemySpecialMissile[i].life == ALIVE) {
            Nokia5110_PrintBMP(enemySpecialMissile[i].x, enemySpecialMissile[i].y,
                    enemySpecialMissile[i].image[enemySpecialMissile[i].frame], 0);
        }
    }

    for (i = 0; i < MAX_SMISSILES; i++) {
        if (playerSpecialMissile[i].life == ALIVE) {
            Nokia5110_PrintBMP(playerSpecialMissile[i].x, playerSpecialMissile[i].y,
                    playerSpecialMissile[i].image[playerSpecialMissile[i].frame], 0);
        }
    }

    for (i = 0; i < MAX_BUNKERS; i++) {
        if (bunker[i].life == ALIVE) {
            Nokia5110_PrintBMP(bunker[i].x, bunker[i].y,
                    bunker[i].image[bunker[i].frame], 0);
        }
    }

    Nokia5110_DisplayBuffer();

    if (playerShip.life == DEAD) {
        Game_Over();
    } else if (j == 0) {
        Game_Win();
    }
}

unsigned long
Game_GetShipPosition(void)
{
    static const float resolution = 3.3/4096;
    float distance = 0, voltage = 0;
    unsigned long result = ADC0_In();
    voltage = result * resolution;
    distance = (voltage * 66.0) / 3.3;
    return (unsigned long)distance;
}

void
Game_FireMissile(int player)
{
    int i;
    int enemyRand; 
    if (player) {
        for (i = 0; i < MAX_PMISSILES; i++) {
            if (playerMissile[i].life == DEAD) {
                playerMissile[i].x = playerShip.x + PLAYERW/2;
                playerMissile[i].y = playerShip.y - PLAYERH;
                playerMissile[i].life = ALIVE;
                Sound_Shoot();
                break;
            }
        }
    } else {
        enemyRand = SRand(ADC0_In()) % MAX_ENEMIES;
        for (i = 0; i < MAX_EMISSILES; i++) {
            if (enemyMissile[i].life == DEAD && 
                    enemy[enemyRand].life == ALIVE) {
                enemyMissile[i].x = enemy[enemyRand].x + ENEMY10W/2;
                enemyMissile[i].y = enemy[enemyRand].y + ENEMY10H;
                enemyMissile[i].life = ALIVE;
                Sound_Shoot();
                break;
            }
        }
    }

}

void
Game_FireSpecialMissile(int player)
{
    int i, enemyRand;
    if (player) {
        for (i = 0; i < MAX_SMISSILES; i++) {
            if (playerSpecialMissile[i].life == DEAD && 
                    playerShip.life == ALIVE) {
                playerSpecialMissile[i].x = playerShip.x + PLAYERW/2;
                playerSpecialMissile[i].y = playerShip.y - PLAYERH;
                playerSpecialMissile[i].life = ALIVE;
                Sound_Shoot();
                break;
            }
        }
    } else {
        enemyRand = SRand(ADC0_In()) % MAX_ENEMIES;
        for (i = 0; i < MAX_SMISSILES; i++) {
            if (enemySpecialMissile[i].life == DEAD && 
                    enemy[enemyRand].life == ALIVE) {
                enemySpecialMissile[i].x = enemy[enemyRand].x + ENEMY10W/2;
                enemySpecialMissile[i].y = enemy[enemyRand].y + ENEMY10H;
                enemySpecialMissile[i].life = ALIVE;
                Sound_Shoot();
                break;
            }
        }
    }
}

void
Game_MoveMissiles(void)
{
    int i;
    for (i = 0; i < MAX_PMISSILES; i++) {
        if (playerMissile[i].life == ALIVE) {
            playerMissile[i].y -= 1;
            if (playerMissile[i].y < MISSILEH) {
                playerMissile[i].life = DEAD;
            }
        }
    }

    for (i = 0; i < MAX_EMISSILES; i++) {
        if (enemyMissile[i].life == ALIVE) {
            enemyMissile[i].y += 1;
            if (enemyMissile[i].y > SCREENH) {
                enemyMissile[i].life = DEAD;
            }
        }
    }

    if (playerSpecialMissile[0].life == ALIVE) {
        playerSpecialMissile[0].y -= 2;
        playerSpecialMissile[0].x -= 1;
        if (playerSpecialMissile[0].y < MISSILEH || 
                playerSpecialMissile[0].x > SCREENW) {
            playerSpecialMissile[0].life = DEAD;
        }
    }

    if (playerSpecialMissile[1].life == ALIVE) {
        playerSpecialMissile[1].y -= 2;
        playerSpecialMissile[1].x += 1;
        if (playerSpecialMissile[1].y < MISSILEH || 
                playerSpecialMissile[1].x > SCREENW) {
            playerSpecialMissile[1].life = DEAD;
        }
    }

    for (i = 0; i < MAX_SMISSILES; i++) {
        if (enemySpecialMissile[i].life == ALIVE) {
            enemySpecialMissile[i].y += 2;
            if (enemySpecialMissile[i].x > playerShip.x) {
                enemySpecialMissile[i].x -= 1;
            } else {
                enemySpecialMissile[i].x += 1;
            }
            if (enemySpecialMissile[i].y > SCREENH) {
                enemySpecialMissile[i].life = DEAD;
            }
        }
    }
}

void
Game_CatchEnemy(void)
{
    int i, j;
    for (i = 0; i < MAX_PMISSILES; i++) {
        if (playerMissile[i].life == ALIVE) {
            for (j = 0; j < MAX_ENEMIES; j++) {
                if (enemy[j].life == ALIVE && 
                        playerMissile[i].x >= enemy[j].x &&
                        playerMissile[i].x <= enemy[j].x + ENEMY10W &&
                        playerMissile[i].y <= enemy[j].y) {
                    enemy[j].life = DEAD;
                    playerMissile[i].life = DEAD;
                    Sound_Explosion();
                }
            }
        }
    }

    for (i = 0; i < MAX_SMISSILES; i++) {
        if (playerSpecialMissile[i].life == ALIVE) {
            for (j = 0; j < MAX_ENEMIES; j++) {
                if (enemy[j].life == ALIVE && 
                        playerSpecialMissile[i].x >= enemy[j].x &&
                        playerSpecialMissile[i].x <= enemy[j].x + ENEMY10W &&
                        playerSpecialMissile[i].y <= enemy[j].y) {
                    enemy[j].life = DEAD;
                    playerSpecialMissile[i].life = DEAD;
                    Sound_Explosion();
                }
            }
        }
    }

}

void
Game_CatchPlayer(void)
{
    int i;
    for (i = 0; i < MAX_EMISSILES; i++) {
        if (enemyMissile[i].life == ALIVE && playerShip.life == ALIVE) {
            if (enemyMissile[i].y >= playerShip.y - PLAYERH &&
                    enemyMissile[i].y <= playerShip.y &&
                    enemyMissile[i].x >= playerShip.x + 2 &&
                    enemyMissile[i].x <= playerShip.x + PLAYERW - 2) {
                playerShip.life = DEAD;
                enemyMissile[i].life = DEAD;
                Sound_Explosion();
            }
        }
    }
    
    for (i = 0; i < MAX_SMISSILES; i++) {
        if (enemySpecialMissile[i].life == ALIVE && playerShip.life == ALIVE) {
            if (enemySpecialMissile[i].y >= playerShip.y - PLAYERH &&
                    enemySpecialMissile[i].y <= playerShip.y &&
                    enemySpecialMissile[i].x >= playerShip.x + 2 &&
                    enemySpecialMissile[i].x <= playerShip.x + PLAYERW - 2) {
                playerShip.life = DEAD;
                enemySpecialMissile[i].life = DEAD;
                Sound_Explosion();
            }
        }
    }
}

void
Game_CatchBunker(void)
{
    int i;
    for (i = 0; i < MAX_EMISSILES; i++) {
        if (enemyMissile[i].life == ALIVE) {
            int j;
            for (j = 0; j < MAX_BUNKERS; j++) {
                if (bunker[j].life == ALIVE &&
                        enemyMissile[i].y >= bunker[j].y - BUNKERH &&
                        enemyMissile[i].y <= bunker[j].y &&
                        enemyMissile[i].x >= bunker[j].x + 2 &&
                        enemyMissile[i].x <= bunker[j].x + BUNKERW - 2) {
                    enemyMissile[i].life = DEAD;
                    bunker[j].frame++;
                    if (bunker[i].frame > 3) {
                        bunker[j].life = DEAD;
                    }
                    Sound_Explosion();
                }
            }
        }
    }
    
    for (i = 0; i < MAX_SMISSILES; i++) {
        if (enemySpecialMissile[i].life == ALIVE) {
            int j;
            for (j = 0; j < MAX_BUNKERS; j++) {
                if (bunker[j].life == ALIVE &&
                        enemySpecialMissile[i].y >= bunker[j].y - BUNKERH &&
                        enemySpecialMissile[i].y <= bunker[j].y &&
                        enemySpecialMissile[i].x >= bunker[j].x + 2 &&
                        enemySpecialMissile[i].x <= bunker[j].x + BUNKERW - 2) {
                    enemySpecialMissile[i].life = DEAD;
                    bunker[j].frame++;
                    if (bunker[i].frame > 3) {
                        bunker[j].life = DEAD;
                    }
                    Sound_Explosion();
                }
            }
        }
    }
}

void
Game_Over(void)
{
    Delay(10);
    Nokia5110_Clear();
    Nokia5110_SetCursor(0, 0);
    Nokia5110_OutString(" GAME OVER!");
    Nokia5110_SetCursor(0, 1);
    Nokia5110_OutString(" Nice Try!");
    Nokia5110_SetCursor(0, 2);
    Nokia5110_OutString(" Press Any");
    Nokia5110_SetCursor(0, 3);
    Nokia5110_OutString(" Key To");
    Nokia5110_SetCursor(0, 4);
    Nokia5110_OutString(" Restart");
    
    DisableInterrupts();
    while (!Weapones_GetButtons()) {
        ; 
    }
    Delay(5);
    Game_CreateObjects();
    EnableInterrupts();
}

void
Game_Win(void)
{
    Delay(10);
    Nokia5110_Clear();
    Nokia5110_SetCursor(0, 0);
    Nokia5110_OutString(" YOU WIN!");
    Nokia5110_SetCursor(0, 1);
    Nokia5110_OutString(" Press Any");
    Nokia5110_SetCursor(0, 2);
    Nokia5110_OutString(" Key To");
    Nokia5110_SetCursor(0, 3);
    Nokia5110_OutString(" Restart");
    
    DisableInterrupts();
    while (!Weapones_GetButtons()) {
        ; 
    }
    Delay(5);
    Game_CreateObjects();
    EnableInterrupts();
}

