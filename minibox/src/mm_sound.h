#ifndef __SOUND_PLAY_H__
#define __SOUND_PLAY_H__

void init_sound_mad();
void sound_using_mad_stop();
void sound_using_mad_play(const char *file);
void play_sound_ogg(const char *file);

#endif
