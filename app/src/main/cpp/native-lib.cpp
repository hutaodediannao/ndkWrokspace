#include <jni.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <android/log.h>
#include <vector>
#include <algorithm>
#include <unistd.h>

#include <base.h>

#define TAG "myLog"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
using namespace std;

extern "C" JNIEXPORT jstring JNICALL
Java_com_app_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

pthread_t pt;
JNIEnv *mEnv;
jobject jo;

void *test(void *vo) {
    LOGI("呆梨下班了...");
    LOGI("线程执行完成...");
//    jclass jcla = mEnv->FindClass("com/app/myapplication/MainActivity");
//    jmethodID jmid = mEnv->GetMethodID(jcla, "updateUI", "(I)V");
//    mEnv->CallVoidMethod(jo, jmid, 250);
    pthread_detach(pt);
    return NULL;
}

void testThread(jobject thiz) {
    int ret = 0;
    ret = pthread_create(&pt, NULL, test, thiz);
    if (ret == -1) {
        LOGI("error");
        return;
    } else {
        LOGI("呆梨开始上班...");
        LOGI("线程创建成功，开始运行...");
        jclass jcla = mEnv->FindClass("com/app/myapplication/MainActivity");
        jmethodID jmid = mEnv->GetMethodID(jcla, "updateUI", "(I)V");
        mEnv->CallVoidMethod(jo, jmid, ret);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_app_myapplication_MainActivity_testPthread(JNIEnv *env, jobject thiz, jint data) {
    mEnv = env;
    jo = thiz;

    testThread(thiz);
}

void f(string str) {
    const char *msg = str.data();
    LOGI("str: %s、\t", msg);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_app_myapplication_MainActivity_listToJNI(JNIEnv *env, jobject thiz, jobject str_list) {
    vector<string> vs;
    for (int i = 0; i < 5; ++i) {
        string s = "oppo";
        vs.push_back(s + to_string(i));
    }
    for_each(vs.begin(), vs.end(), f);
}

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGI("native-lib JNI_OnLoad() 函数开始自动调用...");
    return JNI_VERSION_1_6;
}

typedef struct {
private:
    string name;
    int mId = 0;

public:
    void init(string name, int id) {
        this->name = name;
        this->mId = id;
    }
    string getName(){
        return this->name;
    }
    int getId(){
        return this->mId;
    }
} Msg;

void *testThread(void *arg) {
    sleep(3);
    Msg *msg = static_cast<Msg *>(arg);
    LOGI("执行参数线程完成: msg.name: %s\tmsg.id: %d\n", msg->getName().data(), msg->getId());
    return NULL;
}

Msg msg;

extern "C"
JNIEXPORT void JNICALL
Java_com_app_myapplication_MainActivity_testPthread2(JNIEnv *env, jobject thiz) {
    pthread_t pt;
    msg.init("nokia", 200);
    LOGI("传递参数为：name:%s\tid:%d", msg.getName().data(), msg.getId());
    pthread_create(&pt, NULL, testThread, &msg);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_app_myapplication_MainActivity_updatePerson(JNIEnv *env, jobject thiz, jobject p, jstring newName) {
    jclass jcla = env->FindClass("com/app/myapplication/Person");
    jboolean isPerson = env->IsInstanceOf(p, jcla);
    if (isPerson) {
        LOGI("is Person ok");
        jmethodID jmd = env->GetMethodID(jcla, "setName", "(Ljava/lang/String;)V");
        env->CallVoidMethod(p, jmd, newName);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_app_myapplication_MainActivity_updatePerson2(JNIEnv *env, jobject thiz, jobject p,
                                                      jstring new_name) {
    jclass jcla = env->FindClass("com/app/myapplication/Person");
    jfieldID jfid = env->GetFieldID(jcla, "name", "Ljava/lang/String;");
    env->SetObjectField(p, jfid, new_name);
    LOGI("调用完成。。。");
}

extern "C" void
Java_com_app_myapplication_MainActivity_updatePerson3(JNIEnv *env, jobject thiz, jobject p3,
                                                      jobject ad) {
    jclass jcla = env->FindClass("com/app/myapplication/Person");
    jfieldID jfid = env->GetFieldID(jcla, "add", "Lcom/app/myapplication/Person$AddRess;");
    env->SetObjectField(p3, jfid, ad);
    LOGI("调用完成。。。");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_app_myapplication_MainActivity_testIncludeLibrary(JNIEnv *env, jobject thiz, jint a,
                                                           jint b) {
    jint sum = add(a, b);
    return sum;
}