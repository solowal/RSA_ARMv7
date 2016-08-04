LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := helloneon

LOCAL_SRC_FILES := helloneon.c

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
    LOCAL_CFLAGS := -DHAVE_NEON=1
    LOCAL_SRC_FILES += arith.c.neon mul.c.neon mont512.c.neon mont1024.c.neon mont2048.c.neon kara_mul.c.neon sqr.c.neon kara_sqr.c.neon rsa_test.c.neon rsa_arith.c.neon
endif

LOCAL_STATIC_LIBRARIES := cpufeatures

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cpufeatures)
