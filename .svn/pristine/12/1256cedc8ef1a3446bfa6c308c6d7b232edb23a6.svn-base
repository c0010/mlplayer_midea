#define LOG_TAG "CMPlayerUtility-JNI"
#include <jni.h>
#include "stdafx.h"
#include "cmplayerutility.h"
#include "cmswap.h"
#include "android/env.h"


struct NativeData {
	CMPlayerUtility* m_pPlayerUtility;
	CMSwap*   m_pSwap;
};

filedsU CMPlayerUtility::field;


static jboolean Java_com_wunding_mlplayer_CMPlayerUtility_Init(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);

	if (!pContext) {
		pContext = new NativeData();
		if (pContext) {
			pContext->m_pSwap = new CMSwap(thiz);
			pContext->m_pPlayerUtility = new CMPlayerUtility(
					pContext->m_pSwap);
		} else {
			delete pContext;
			return JNI_FALSE;
		}
		env->SetIntField(thiz, CMPlayerUtility::field.mContext, int(pContext));
	} else
		return JNI_FALSE;

	if (pContext->m_pPlayerUtility->Init())
		return JNI_TRUE;
	return JNI_FALSE;
}
// Description: Creates instance of network datasource and open it.
// param sUrl: Opening url.
// param nMode: Mode of dest.
// Return: none.
static void Java_com_wunding_mlplayer_CMPlayerUtility_OpenUrl(JNIEnv *env,
		jobject thiz, jstring sUrl, jint nMode,jstring sFilName) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	const char* purl = env->GetStringUTFChars(sUrl, NULL);
	if (!purl)
		return;
	const char* pFilName = env->GetStringUTFChars(sFilName, NULL);
	if (!pFilName)
		return;
	pContext->m_pPlayerUtility->OpenUrl(purl, nMode, pFilName);
	env->ReleaseStringUTFChars(sUrl, purl);
	env->ReleaseStringUTFChars(sFilName, pFilName);
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_OpenFile(JNIEnv *env,
		jobject thiz, jstring sFileName, jint nMode) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	const char* pFileName = env->GetStringUTFChars(sFileName, NULL);
	if (!pFileName)
		return;
	pContext->m_pPlayerUtility->OpenFile(pFileName, nMode);
	env->ReleaseStringUTFChars(sFileName, pFileName);
}

// Description: Play audio and video.
// Return: none.
static void Java_com_wunding_mlplayer_CMPlayerUtility_Play(JNIEnv *env, jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->Play();
}

// Description: Pause audio and video.
// Return: none.
static void Java_com_wunding_mlplayer_CMPlayerUtility_Pause(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->Pause();
}

// Description: Stop audio and video, reset buffer, set DataInter's pos to 0.
// Return: none.
static void Java_com_wunding_mlplayer_CMPlayerUtility_Stop(JNIEnv *env, jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->Stop();

}
// Description: Close DataInter, audio and video and reset all.
// Return: none.
static void Java_com_wunding_mlplayer_CMPlayerUtility_Close(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->Close();

	delete pContext->m_pPlayerUtility;
	delete pContext->m_pSwap;
	pContext->m_pSwap = NULL;
	pContext->m_pPlayerUtility = NULL;
	delete pContext;
	pContext = NULL;

	env->SetIntField(thiz, CMPlayerUtility::field.mContext, 0);
}

static jint Java_com_wunding_mlplayer_CMPlayerUtility_Duration(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return 0;
	return pContext->m_pPlayerUtility->Duration();
}

static jint Java_com_wunding_mlplayer_CMPlayerUtility_GetPosition(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return 0;
	return pContext->m_pPlayerUtility->GetPosition();
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_SetPosition(JNIEnv *env,
		jobject thiz, jint nPos) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetPosition(nPos);
}

static jint Java_com_wunding_mlplayer_CMPlayerUtility_MaxVolume(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return 0;
	return pContext->m_pPlayerUtility->MaxVolume();
}

static jint Java_com_wunding_mlplayer_CMPlayerUtility_GetVolume(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return 0;
	return pContext->m_pPlayerUtility->GetVolume();
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_SetVolume(JNIEnv *env,
		jobject thiz, jint nVolume) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetVolume(nVolume);
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_SetVolPer(JNIEnv *env,
		jobject thiz, jint nPer) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetVolPer(nPer);
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_VolUp(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->VolUp();
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_VolDown(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->VolDown();
}

static jint Java_com_wunding_mlplayer_CMPlayerUtility_GetRotation(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return 0;
	return pContext->m_pPlayerUtility->GetRotation();
}

static jint Java_com_wunding_mlplayer_CMPlayerUtility_GetOpenType(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return 0;
	return pContext->m_pPlayerUtility->GetOpenType();
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_SetRotation(JNIEnv *env,
		jobject thiz, jint nRotation) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetRotation(nRotation);
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_SetDrawSize(JNIEnv *env,
		jobject thiz, jint nWidth, jint nHeight) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetDrawSize(nWidth, nHeight);

}
static void Java_com_wunding_mlplayer_CMPlayerUtility_SetBufTime(JNIEnv *env,
		jobject thiz, jint nBufTime) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetBufTime(nBufTime);
}

static jboolean Java_com_wunding_mlplayer_CMPlayerUtility_IsPlaying(JNIEnv *env,
		jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return JNI_FALSE;
	if (pContext->m_pPlayerUtility->IsPlaying())
		return JNI_TRUE;
	return JNI_FALSE;
}

static jboolean Java_com_wunding_mlplayer_CMPlayerUtility_IsDataCompleted(
		JNIEnv *env, jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return JNI_FALSE;
	if (pContext->m_pPlayerUtility->IsDataCompleted())
		return JNI_TRUE;
	return JNI_FALSE;
}

static void Java_com_wunding_mlplayer_CMPlayerUtility_SetManuPause(
		JNIEnv *env, jobject thiz, jboolean pause) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return;
	pContext->m_pPlayerUtility->SetManuPause(pause);
}

static jboolean Java_com_wunding_mlplayer_CMPlayerUtility_IsManuPause(
		JNIEnv *env, jobject thiz) {
	NativeData* pContext = (NativeData*) env->GetIntField(thiz,
			CMPlayerUtility::field.mContext);
	if (!pContext)
		return JNI_FALSE;
	if (pContext->m_pPlayerUtility->IsManuPause())
		return JNI_TRUE;
	return JNI_FALSE;
}

//Table of methods associated with a single class.
static JNINativeMethod gMethods[] =
		{
				/* name, signature, funcPtr */
				{ "Init", "()Z",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_Init },
				{
						"OpenUrl",
						"(Ljava/lang/String;ILjava/lang/String;)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_OpenUrl },
				{
						"OpenFile",
						"(Ljava/lang/String;I)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_OpenFile },
				{ "Play", "()V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_Play },
				{ "Pause", "()V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_Pause },
				{ "Stop", "()V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_Stop },
				{ "Close", "()V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_Close },
				{
						"Duration",
						"()I",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_Duration },
				{
						"GetPosition",
						"()I",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_GetPosition },
				{
						"SetPosition",
						"(I)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetPosition },
				{
						"MaxVolume",
						"()I",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_MaxVolume },
				{
						"GetVolume",
						"()I",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_GetVolume },
				{
						"SetVolume",
						"(I)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetVolume },
				{
						"SetVolPer",
						"(I)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetVolPer },
				{ "VolUp", "()V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_VolUp },
				{
						"VolDown",
						"()V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_VolDown },
				{
						"GetRotation",
						"()I",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_GetRotation },
				{
						"GetOpenType",
						"()I",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_GetOpenType },

				{
						"SetRotation",
						"(I)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetRotation },
				{
						"SetDrawSize",
						"(II)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetDrawSize },
				{
						"SetBufTime",
						"(I)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetBufTime },
				{
						"IsPlaying",
						"()Z",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_IsPlaying },
				{
						"IsDataCompleted",
						"()Z",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_IsDataCompleted },
				{
						"SetManuPause",
						"(Z)V",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_SetManuPause },
				{
						"IsManuPause",
						"()Z",
						(void*) Java_com_wunding_mlplayer_CMPlayerUtility_IsManuPause },


		};

//#include <SDL.h>
///* Include the SDL main definition header */
//#include "SDL_main.h"
//extern void SDL_Android_Init(JNIEnv* env, jclass cls);
//void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls)
//{
//    /* This interface could expand with ABI negotiation, calbacks, etc. */
//    SDL_Android_Init(env, cls);
//
//    SDL_SetMainReady();
//
//    /* Run the application code! */
//    int status;
//    char *argv[2];
//    argv[0] = SDL_strdup("SDL_app");
//    argv[1] = NULL;
//    status = SDL_main(1, argv);
//
//    /* Do not issue an exit or the whole application will terminate instead of just the SDL thread */
//    /* exit(status); */
//}

extern "C" void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls);
static JNINativeMethod gMethodSs[] =
		{
				/* name, signature, funcPtr */
				{ "nativeInit", "()V",
						(void*) Java_org_libsdl_app_SDLActivity_nativeInit },
		};

int registerPlayerMethods(JNIEnv* env) {
	static const char* const kClassName = "com/wunding/mlplayer/CMPlayerUtility";
	/* look up the class */
	jclass clazz = env->FindClass(kClassName);
	if (!clazz) {
		CM_ERRP("Can't find class %s", kClassName);
		return -1;
	}

	/* register all the methods */
	if (env->RegisterNatives(clazz, gMethods,
			sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK) {
		CM_ERRP("Failed registering methods for %s/n", kClassName);
		return -1;
	}

	CMPlayerUtility::field.mContext = env->GetFieldID(clazz, "mNativeContext", "I");
    if (CMPlayerUtility::field.mContext == 0) {
        CM_ERR("CMPlayerUtility::field no found mContext");
        return -1;
    }

    CMPlayerUtility::field.PostToFunc = env->GetMethodID(clazz, "PostToFunc", "(III)V");
    if (CMPlayerUtility::field.PostToFunc == NULL) {
        CM_ERR("CMPlayerUtility::field no found PostToFunc");
        return -1;
    }

    CMPlayerUtility::field.VideoDrawFunc = env->GetMethodID(clazz, "PostToVideoDraw", "([III)V");
    if (CMPlayerUtility::field.VideoDrawFunc == NULL) {
        CM_ERR("CMPlayerUtility::field no found VideoDrawFunc");
        return -1;
    }

    static const char* const kClassNameV = "org/libsdl/app/SDLActivity";
	clazz = env->FindClass(kClassNameV);
	if (!clazz) {
		CM_ERRP("Can't find class %s", kClassNameV);
		return -1;
	}
	if (env->RegisterNatives(clazz, gMethodSs,
			sizeof(gMethodSs) / sizeof(gMethodSs[0])) != JNI_OK) {
		CM_ERRP("Failed registering methods for %s/n", kClassNameV);
		return -1;
	}

//	static const char* const kClassNameA = "android/media/AudioTrack";
//
//	clazz = env->FindClass(kClassNameA);
//	if (!clazz) {
//		CM_ERRP("Can't find class %s", kClassNameA);
//		return -1;
//	}

//    CMAudioPlay::field.audioClass = (jclass)env->NewGlobalRef(clazz);
//    if (CMAudioPlay::field.audioClass == NULL) {
//        CM_ERR("CMAudioPlay::field no found audioClass");
//        return -1;
//    }
//
//    CMAudioPlay::field.construction_id = env->GetMethodID(clazz, "<init>", "(IIIIII)V");
//    if (CMAudioPlay::field.construction_id == NULL) {
//        CM_ERR("CMAudioPlay::field no found construction_id");
//        return -1;
//    }
//
//    CMAudioPlay::field.getMinBufferSize_method = env->GetStaticMethodID(clazz, "getMinBufferSize", "(III)I");
//    if (CMAudioPlay::field.getMinBufferSize_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found getMinBufferSize_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.getState_method = env->GetMethodID(clazz, "getState", "()I");
//    if (CMAudioPlay::field.getState_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found getState_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.play_method = env->GetMethodID(clazz, "play", "()V");
//    if (CMAudioPlay::field.play_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found play_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.pause_method = env->GetMethodID(clazz, "pause", "()V");
//    if (CMAudioPlay::field.pause_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found pause_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.stop_method = env->GetMethodID(clazz, "stop", "()V");
//    if (CMAudioPlay::field.stop_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found stop_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.release_method = env->GetMethodID(clazz, "release", "()V");
//    if (CMAudioPlay::field.release_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found release_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.getMaxVolume_method = env->GetStaticMethodID(clazz, "getMaxVolume", "()F");
//    if (CMAudioPlay::field.getMaxVolume_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found getMaxVolume_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.getMinVolume_method = env->GetStaticMethodID(clazz, "getMinVolume", "()F");
//    if (CMAudioPlay::field.getMinVolume_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found getMinVolume_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.setStereoVolume_method = env->GetMethodID(clazz, "setStereoVolume", "(FF)I");
//    if (CMAudioPlay::field.setStereoVolume_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found setStereoVolume_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.write_method = env->GetMethodID(clazz, "write", "([BII)I");
//    if (CMAudioPlay::field.write_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found write_method");
//        return -1;
//    }
//
//    CMAudioPlay::field.getPlayState_method = env->GetMethodID(clazz, "getPlayState", "()I");
//    if (CMAudioPlay::field.getState_method == NULL) {
//        CM_ERR("CMAudioPlay::field no found getPlayState_method");
//        return -1;
//    }

	return 0;
}


