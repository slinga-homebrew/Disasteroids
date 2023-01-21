#pragma once

void updateTitleScreenShips(void);
void drawTitleScreenShips(void);
void destroyPlayer(PPLAYER player);

void drawPlayers(void);

void spawnPlayer(PPLAYER player, int angle);
void spawnPlayers(void);

void initPlayers(void);
unsigned int countAlivePlayers(void);
