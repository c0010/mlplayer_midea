#ifndef __AVPLAYER__H
#define __AVPLAYER__H


#define FF_ALLOC_EVENT     (SDL_USEREVENT)
#define FF_REFRESH_EVENT   (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT      (SDL_USEREVENT + 2)
#define FF_OPEN_EVENT      (SDL_USEREVENT + 3)
#define FF_CLOSE_EVENT     (SDL_USEREVENT + 4)
#define FF_PLAY_EVENT      (SDL_USEREVENT + 5)
#define FF_PAUSE_EVENT     (SDL_USEREVENT + 6)
#define FF_PLAYPAUSE_EVENT (SDL_USEREVENT + 7)
#define FF_STOP_EVENT      (SDL_USEREVENT + 8)
#define FF_SEEK_EVENT      (SDL_USEREVENT + 9)

#define FF_INTERRUPT_START_EVENT (SDL_USEREVENT + 10)
#define FF_INTERRUPT_END_EVENT   (SDL_USEREVENT + 11)

#ifdef __cplusplus
extern "C" {
#endif

int av_duration();
int av_getposition();
void av_setposition(int pos);
int av_maxvolume();
int av_getvolume();
void av_pause();
void av_play();
void av_stop();
void av_playpause();
int av_isplaying();

#if defined(__IPHONE_OS__)
//ios phone call will end avaudosession.need reopen
void av_interrupt_start();
void av_interrupt_end();
#endif

#ifdef __cplusplus
};
#endif

#endif
