LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := PCCamera
LOCAL_SRC_FILES := main.cpp
LOCAL_CPPFLAGS  := -O2 -std=c++17 -fno-rtti -fno-exceptions
LOCAL_LDLIBS    := -llog
LOCAL_C_INCLUDES := $(LOCAL_PATH)
include $(BUILD_SHARED_LIBRARY)
