#include "basetypes.hpp"

jobject_wrap::jobject_wrap(JNIEnv *env, jobject obj){
  this->env = env;
  this->obj = env->NewGlobalRef(obj);
};

jobject_wrap::~jobject_wrap(){
  this->env->DeleteGlobalRef(this->obj);
};
jobject jobject_wrap::getObject(){
  return this->obj;
};
