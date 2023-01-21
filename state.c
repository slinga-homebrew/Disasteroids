#include "main.h"
#include "state.h"
#include "util.h"
#include "gameplay.h"
#include "ssmtf_logo.h"
#include "title_screen.h"
#include "assets/audio.h"

// transistions between game states
void transitionState(GAME_STATE newState)
{
    jo_clear_screen();

    switch(newState)
    {
        case GAME_STATE_SSMTF_LOGO:
        {
            playCDTrack(TITLE_TRACK);
            ssmtfLogo_init();
            g_Game.gameState = GAME_STATE_SSMTF_LOGO;
            break;
        }
        case GAME_STATE_TITLE_SCREEN:
        {
            // if coming from SSMTF screen, don't restart the audio
            if(g_Game.gameState != GAME_STATE_SSMTF_LOGO)
            {
                playCDTrack(TITLE_TRACK);
            }
            titleScreen_init();
            g_Game.gameState = GAME_STATE_TITLE_SCREEN;
            break;
        }
        case GAME_STATE_GAMEPLAY:
        {
            jo_audio_stop_cd();
            gameplay_init();
            g_Game.gameState = GAME_STATE_GAMEPLAY;
            break;
        }
        default:
        {
            return;
        }
    }

    return;
}
