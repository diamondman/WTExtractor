/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class wtgutils_com_Loader */

#ifndef _Included_wtgutils_com_Loader
#define _Included_wtgutils_com_Loader
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     wtgutils_com_Loader
 * Method:    getPath
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_wtgutils_com_Loader_getPath
  (JNIEnv *, jobject);

/*
 * Class:     wtgutils_com_Loader
 * Method:    loadClass
 * Signature: (Ljava/lang/String;)Lcom/ms/com/Variant;
 */
JNIEXPORT jobject JNICALL Java_wtgutils_com_Loader_loadClass
  (JNIEnv *, jobject, jstring);

/*
 * Class:     wtgutils_com_Loader
 * Method:    setProduct
 * Signature: (Ljava/lang/String;IIIILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_wtgutils_com_Loader_setProduct
  (JNIEnv *, jobject, jstring, jint, jint, jint, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
