#ifndef __IMCOMMON_H__
#define __IMCOMMON_H__


#include <jni.h>
#include "cmcommon.h"
#include "utf8ncpy.h"

struct fields_t {
    jmethodID callback;       //... callback method
    jfieldID  nativeJavaObj;  // stores in Java the native object
    jfieldID  jniData;        // stores in Java additional resources
};

struct callback_cookie {
    jclass      info_class;
    jobject     ref;
};

class CMUpdateDataListener : public IMUpdateDataListener
{
public:
    CMUpdateDataListener(jmethodID funcID);
    virtual ~CMUpdateDataListener();
    virtual void OnUpdateDataProgress(void* UserData, int nPercent);
    virtual void OnUpdateDataFinish(void* UserData, int Result);
private:
    jmethodID mFuncID;
};

class CMSimpleResultListener : public IMSimpleResultListener
{
public:
    CMSimpleResultListener(jmethodID funcID);
    virtual ~CMSimpleResultListener();
    virtual void OnRequestFinish(void* UserData, int Result);
private:
    jmethodID mFuncID;
};

class CMLoginListener : public IMLoginListener
{
public:
    CMLoginListener(jmethodID funcID);
    virtual ~CMLoginListener();
    virtual void OnLogin(void* UserData, int Result, int HasNewVersion);
private:
    jmethodID mFuncID;
};

class CMRatingListener : public IMRatingListener
{
public:
    CMRatingListener(jmethodID funcID);
    virtual ~CMRatingListener();
    virtual void OnRating(void* UserData, int nNewRating, int Result);
private:
    jmethodID mFuncID;
};

class CMGetImageListener : public IMGetImageListener
{
public:
    CMGetImageListener(jmethodID funcID);
    virtual ~CMGetImageListener();
    virtual void OnFinish(void* UserData, int Result, int nID);
private:
    jmethodID mFuncID;
};


#endif

