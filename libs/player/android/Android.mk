# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)/..


include $(CLEAR_VARS)
                
LOCAL_MODULE    := player
    
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS     := -DHAVE_STDINT_H -DSTDC_HEADERS

LOCAL_C_INCLUDES  += $(LOCAL_PATH) $(LOCAL_PATH)/../include $(LOCAL_PATH)/android $(LOCAL_PATH)/include $(LOCAL_PATH)/include/SDL2  $(LOCAL_PATH)/../tools $(LOCAL_PATH)/../business_model $(LOCAL_PATH)/../sqlite $(LOCAL_PATH)/../xmlparser $(LOCAL_PATH)/../network $(LOCAL_PATH)/../minizip

LOCAL_SRC_FILES := cmplayerutility.cpp \
		   avplayer.c \
		   android/SDL_android_main.c \
		   android/cmswap.cpp \
		   android/com_wunding_mlplayer_CMPlayerUtility.cpp 
		  

LOCAL_LDLIBS := -lGLESv1_CM -llog -lz

ifeq ($(LIBS_BUILD_SHARED),)
include $(BUILD_STATIC_LIBRARY)
else
LOCAL_C_INCLUDES  += $(LOCAL_PATH)/../../../libs
LOCAL_STATIC_LIBRARIES := SDL2 avresample avformat avfilter swscale avcodec avutil faac x264 opencore-amrnb 
#LOCAL_SHARED_LIBRARIES := network tools
include $(BUILD_SHARED_LIBRARY)
endif

