#pragma once

// CD sound tracks
// track 1 is the game data
#define TITLE_TRACK         (2)
#define PAUSE_TRACK         (3)
#define VICTORY_TRACK       (4)
#define GAME_OVER_TRACK     (5)

void playCDTrack(int track);
void loadPCMAssets(void);
