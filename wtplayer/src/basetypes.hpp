#pragma once

#include <memory>
#include <jni.h>

class jobject_wrap {
public:
  jobject_wrap(JNIEnv *env, jobject obj);
  ~jobject_wrap();
  jobject getObject();

private:
  JNIEnv *env;
  jobject obj;
};

typedef std::shared_ptr<jobject_wrap> jobject_ptr;
typedef jobject_ptr VARIANT;
