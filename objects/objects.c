#include "objects.h"
#include "../gameplay_constants.h"

// allow game objects to wrap the screen
void boundGameplayObject(PGAME_OBJECT gameObject)
{
    if(gameObject->curPos.x < SCREEN_MIN_X)
    {
        gameObject->curPos.x = SCREEN_MAX_X;
    }
    else if(gameObject->curPos.x > SCREEN_MAX_X)
    {
        gameObject->curPos.x = SCREEN_MIN_X;
    }

    if(gameObject->curPos.y < SCREEN_MIN_Y)
    {
        gameObject->curPos.y = SCREEN_MAX_Y;
    }
    else if(gameObject->curPos.y > SCREEN_MAX_Y)
    {
        gameObject->curPos.y = SCREEN_MIN_Y;
    }
}
