LOCAL_PATH:= $(call my-dir)/..

include $(CLEAR_VARS)

LOCAL_MODULE:= network

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
	cmhttpc.cpp \
	cmhttpc_curl.cpp \
	cmnetworkmgr.cpp \
	desencrypt.cpp \
	cmdownloader.cpp \
	android/cmnetworkmgr_and.cpp \
	android/cmdownloader_jni.cpp 

#LOCAL_SRC_FILES := $(addprefix ../,$(COMMON_SOURCES)) $(ANDROID_SOURCES)

LOCAL_C_INCLUDES += $(LOCAL_PATH) $(LOCAL_PATH)/../include $(LOCAL_PATH)/../tools $(LOCAL_PATH)/../xmlparser $(LOCAL_PATH)/../curl/include  $(LOCAL_PATH)/../openssl/include

ifeq ($(LIBS_BUILD_SHARED),)
include $(BUILD_STATIC_LIBRARY)
LOCAL_SHARED_LIBRARIES := crypto ssl
else
LOCAL_SHARED_LIBRARIES := tools crypto ssl
include $(BUILD_SHARED_LIBRARY)
endif




