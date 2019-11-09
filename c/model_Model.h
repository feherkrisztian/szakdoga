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
 * Method:    getStateLength
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_model_Model_getStateLength
  (JNIEnv *, jobject);

/*
 * Class:     model_Model
 * Method:    getInitialState
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_model_Model_getInitialState
  (JNIEnv *, jobject);

/*
 * Class:     model_Model
 * Method:    getNumberOfTransitions
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_model_Model_getNumberOfTransitions
  (JNIEnv *, jobject);

/*
 * Class:     model_Model
 * Method:    getDM
 * Signature: ()[[I
 */
JNIEXPORT jobjectArray JNICALL Java_model_Model_getDM
  (JNIEnv *, jobject);

/*
 * Class:     model_Model
 * Method:    getNextState
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_model_Model_getNextState
  (JNIEnv *, jobject, jintArray);

#ifdef __cplusplus
}
#endif
#endif