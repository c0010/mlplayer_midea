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
                
LOCAL_MODULE    := sqlite3
    
LOCAL_ARM_MODE := arm

LOCAL_CFLAGS     := -DHAVE_STDINT_H -DSTDC_HEADERS

LOCAL_C_INCLUDES  += $(LOCAL_PATH)

LOCAL_SRC_FILES := sqlite3.c

LOCAL_LDLIBS := -llog -lm

ifeq ($(LIBS_BUILD_SHARED),)
include $(BUILD_STATIC_LIBRARY)
else
include $(BUILD_SHARED_LIBRARY)
endif

