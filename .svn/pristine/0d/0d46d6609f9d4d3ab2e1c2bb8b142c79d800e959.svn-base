#include <SDL.h>
/* Include the SDL main definition header */
#include "SDL_main.h"

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
#include <jni.h>
#include <android/log.h>

/* Called before SDL_main() to initialize JNI bindings in SDL library */
extern void SDL_Android_Init(JNIEnv* env, jclass cls);


#define FF_OPEN_EVENT    (SDL_USEREVENT + 3)
#define FF_CLOSE_EVENT    (SDL_USEREVENT + 4)

///* Load */
//void Java_cn_roybi_avplayer_PlayerActivity_nativeLoad(
//                                    JNIEnv* env, jclass cls, jstring url)
//{
//    /* Inject a SDL_QUIT event */
//	SDL_Event event;
//	int len;
//	char* s;
//	const char* sUrl;
//
//    event.type = FF_OPEN_EVENT;
//    sUrl = (*env)->GetStringUTFChars(env, url, NULL);
//    len = strlen(sUrl) + 1;
//    s = SDL_malloc(len);
//	SDL_memcpy(s, sUrl, len);
//    event.user.data1 = s;
//    (*env)->ReleaseStringUTFChars(env, url, sUrl);
//
//    SDL_PushEvent(&event);
//    __android_log_print(ANDROID_LOG_INFO, "PlayerActivity", "PlayerActivity_nativeLoad: %s", s);
//}

/* Start up the SDL app */
void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls)
{
    /* This interface could expand with ABI negotiation, calbacks, etc. */
    SDL_Android_Init(env, cls);

    SDL_SetMainReady();

    /* Run the application code! */
    int status;
    char *argv[2];
    argv[0] = SDL_strdup("SDL_app");
    argv[1] = NULL;
    status = SDL_main(1, argv);

    /* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
    /* exit(status); */
}

