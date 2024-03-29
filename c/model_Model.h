/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class model_Model */

#ifndef _Included_model_Model
#define _Included_model_Model
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     model_Model
 * Method:    load_model
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_model_Model_load_1model
  (JNIEnv *, jobject, jstring);

/*
 * Class:     model_Model
 * Method:    get_initial_state
 * Signature: (J)[I
 */
JNIEXPORT jintArray JNICALL Java_model_Model_get_1initial_1state
  (JNIEnv *, jobject, jlong);

/*
 * Class:     model_Model
 * Method:    get_next_state
 * Signature: (JI[I)I
 */
JNIEXPORT jint JNICALL Java_model_Model_get_1next_1state
  (JNIEnv *, jobject, jlong, jint, jintArray);

#ifdef __cplusplus
}
#endif
#endif
