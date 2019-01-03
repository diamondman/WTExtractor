#include <jni.h>
#include <iostream>
#include <memory>
#include <experimental/filesystem>
//#include <filesystem> // Once I get a newer compiler, flip to 2017 standard.

#include "wtgutils_com_Loader.h"
#include "WTPlayerMain.h"

#include "dshfl.h"
#include "dataaccessors.h"

std::experimental::filesystem::path loaderpath("");

/*
 * Class:     wtgutils_com_Loader
 * Method:    getPath
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_wtgutils_com_Loader_getPath
  (JNIEnv *env, jobject jself) {
  return env->NewStringUTF(loaderpath.c_str());
}

jint throwNoSuchFileException( JNIEnv *env, const char *message )
{
    jclass exClass = env->FindClass("java/nio/file/NoSuchFileException");
    return env->ThrowNew(exClass, message);
}

jint throwIOException( JNIEnv *env, const char *message )
{
    jclass exClass = env->FindClass("java/io/IOException");
    return env->ThrowNew(exClass, message);
}

jint throwOutOfMemoryError( JNIEnv *env, const char *message )
{
    jclass exClass = env->FindClass("java/lang/OutOfMemoryError");
    return env->ThrowNew(exClass, message);
}

/*
 * Class:     wtgutils_com_Loader
 * Method:    loadClass
 * Signature: (Ljava/lang/String;)Lcom/ms/com/Variant;
 */
JNIEXPORT jobject JNICALL Java_wtgutils_com_Loader_loadClass
  (JNIEnv *env, jobject jself, jstring jpath_in) {

  const char* cpath_in = env->GetStringUTFChars(jpath_in, 0);
  std::string path_in(cpath_in);
  env->ReleaseStringUTFChars(jpath_in, cpath_in);

  std::experimental::filesystem::path fullpath = loaderpath / path_in;
  std::shared_ptr<DataAccessor> acc(openFileAccessor(fullpath.c_str()),
                                    freeFileAccessor);
  if(acc == NULL) {
    throwNoSuchFileException(env, fullpath.c_str());
    return 0;
  }

  std::shared_ptr<DSHFL> dshfl(DSHFL_create(acc.get()), DSHFL_free);
  if(dshfl == NULL) {
    throwOutOfMemoryError(env, "Failed to create De-SHuFfLer");
    return 0;
  }
  if(!dshfl->valid) {
    throwIOException(env,
                     "File too short! Header expects more bytes than available!");
    return 0;
  }

  std::shared_ptr<unsigned char> decodebuff
    (new unsigned char[dshfl->header.length],
     [](unsigned char *b){delete[] b;});
  DSHFL_decodeAllChunks(dshfl.get(), decodebuff.get());
  jbyteArray bytearray = env->NewByteArray(dshfl->header.length);
  env->SetByteArrayRegion(bytearray, 0, dshfl->header.length,
                          (jbyte*)decodebuff.get());

  jclass cls = env->FindClass("com/ms/com/Variant");
  if(cls == NULL) return 0;
  jmethodID constructor = env->GetMethodID(cls, "<init>", "()V");
  if(constructor == NULL) return 0;
  jmethodID mputSafeArray = env->GetMethodID(cls, "putSafeArray", "([B)V");
  if(mputSafeArray == NULL) return 0;
  jobject object = env->NewObject(cls, constructor);
  if(object == NULL) return 0;

  env->CallVoidMethod(object, mputSafeArray, bytearray);

  return object;
}

/*
 * Class:     wtgutils_com_Loader
 * Method:    setProduct
 * Signature: (Ljava/lang/String;IIIILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_wtgutils_com_Loader_setProduct
  (JNIEnv *env, jobject jself, jstring s1, jint i1, jint i2, jint i3, jint i4, jstring s2) {
  return 1;
}


/////////////////////////////////////////
/*
 * Class:     WTPlayerMain
 * Method:    setPathForWtNativeLoader
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_WTPlayerMain_setPathForWtNativeLoader
  (JNIEnv *env, jclass cls, jstring jpath_in) {
  const char* cpath_in = env->GetStringUTFChars(jpath_in, 0);
  loaderpath = std::experimental::filesystem::path(cpath_in);
  env->ReleaseStringUTFChars(jpath_in, cpath_in);
}
