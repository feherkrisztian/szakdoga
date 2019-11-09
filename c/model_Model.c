// Save as "HelloJNI.c"
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include <stdbool.h>
#include "model_Model.h"   // Generated
#include "modelloader.h"
#include "pins/pins.h"

static struct
{
	lts_type_t ltstype;
	model_t model_t;
	int N; // length of the state vector
	int K; // number of transitions
} model;

JNIEXPORT void JNICALL Java_model_Model_load_1model(JNIEnv *env, jobject thisObj, jstring path) {
  char* params[2];
  params[0] = "pinswrapper";
  params[1] = (*env)->GetStringUTFChars(env, path, NULL);

  printf("Loading model from %s \n", params[1]);

  model.model_t = getModel(params);
  model.ltstype = GBgetLTStype(model.model_t);
  model.N = lts_type_get_state_length(model.ltstype);
  model.K = dm_nrows(GBgetDMInfo(model.model_t));

  printf("Model loaded\n\n");
}

JNIEXPORT jint JNICALL Java_model_Model_getStateLength(JNIEnv * env, jobject thisObj){
  	return model.N;
}


JNIEXPORT jint JNICALL Java_model_Model_getNumberOfTransitions(JNIEnv * env, jobject thisObj){
	return model.K;
}

JNIEXPORT jintArray JNICALL Java_model_Model_getInitialState(JNIEnv * env, jobject thisObj){
	int GB_initial_state[model.N];
	GBgetInitialState(model.model_t, GB_initial_state);

	jintArray initial_state = (jintArray)(*env)->NewIntArray(env, model.N);
	if(initial_state == NULL) {
    	return NULL;
  	}
	jint *int_ptr = calloc(model.N, sizeof(jint));
	if(int_ptr == NULL) {
		return NULL;
	}
	for(int i=0; i < model.N; i++) {
	    int_ptr[i] = GB_initial_state[i];
	}

	(*env)->SetIntArrayRegion(env,initial_state,0,model.N,(jint*) int_ptr);
 
	free(int_ptr);

	return initial_state;
}

JNIEXPORT jobjectArray JNICALL Java_model_Model_getDM(JNIEnv * env, jobject thisObj){
	matrix_t* m = GBgetDMInfo(model.model_t);

	jclass intClass = (*env)->FindClass(env, "[I");
	jobjectArray transitions = (*env)->NewObjectArray(env, model.K, intClass, env);

	for (int i = 0; i < model.K; i++) {
		int DMStateDep[model.N];
		for (int j = 0; j < model.N; j++) {
            DMStateDep[j] = dm_is_set(m, i, j);
        }
        printf("\n");
        jintArray stateDep = (*env)->NewIntArray(env, model.N);
        (*env)->SetIntArrayRegion(env, stateDep, 0, model.N, DMStateDep);
        (*env)->SetObjectArrayElement(env, transitions, i, stateDep);
        (*env)->DeleteLocalRef(env, stateDep);
	}

    return transitions;
}

static void cb(JNIEnv * env, transition_info_t *ti, int *dst, int *cpy){
	(*env)->CallVoidMethod(env, )
}

JNIEXPORT void JNICALL Java_model_Model_getNextState(JNIEnv * env, jobject thisObj, jintArray jstate){
  jsize len = (*env)->GetArrayLength(env, jstate);
  jint *state = (*env)->GetIntArrayElements(env, jstate, 0);
  for (int i = 0; i < model.K; ++i)
  {
	int c = GBgetTransitionsLong(model.model_t, i, state, cb, NULL);
	printf("c = %d\n", c);
  }
  printstate(state);
}

void printstate(int* state){
	for (int i = 0; i < model.N; ++i)
	{
		printf("%d\n", state[i]);
	}
}

