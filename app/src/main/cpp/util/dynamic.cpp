//
// Created by hutao on 2022-3-20.
//

#include <jni.h>
#include <base.h>
#include <jvm.h>

#include <android/log.h>

#define TAG "dynamicTag"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#define JAVA_CLASS "com/app/myapplication/DynamicJNI"

jstring getMessage(JNIEnv *env, jobject job) {
    return env->NewStringUTF("this is a good ideal!");
}

jint plus(JNIEnv *env, jobject job, int x, int y) {
    return x + y;
}

static JNINativeMethod getMethods[] = {
        {"getNativeString", "()Ljava/lang/String;", (void *) getMessage},
        {"sum",             "(II)I",                (void *) plus}
};

int registerNativeMethods(JNIEnv *env,
                           const char *name, JNINativeMethod *methods, jint nMethods) {
    jclass cla;
    cla = env->FindClass(name);
    if (cla == nullptr) {
        LOGE("registNativeMethods is Error!");
        return JNI_FALSE;
    }
    if (env->RegisterNatives(cla, methods, nMethods) < 0) {
        LOGE("RegisterNatives ERROR ！");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("dynamic JIN_OnLoad() start running...");
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        LOGE("jniOnLoad is Failed!");
        return JNI_FALSE;
    }

    jint result = registerNativeMethods(env, JAVA_CLASS, getMethods, 2);
    if (result == JNI_TRUE) {
        LOGI("注册方法成功");
    } else {
        LOGE("注册方法失败");
    }

    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("dynamic JNI_OnUnload() start running...");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_app_myapplication_DynamicJNI_getSum(JNIEnv *env, jobject thiz, jint a, jint b) {
    jint sum = add(a, b);
    return sum;
}
