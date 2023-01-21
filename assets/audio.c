#include <jo/jo.h>
#include "audio.h"
#include "assets.h"

// play specified audio track
void playCDTrack(int track)
{
    jo_audio_play_cd_track(track, track, false);
}

// load PCM audio
void loadPCMAssets(void)
{
    jo_audio_load_pcm("POP.PCM", JoSoundMono8Bit, &g_Assets.popPCM);
    g_Assets.popPCM.sample_rate = 27086;
}
