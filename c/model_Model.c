// Save as "HelloJNI.c"
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include <stdbool.h>
#include "model_Model.h"   // Generated
#include "modelloader.h"
#include "pins/pins.h"

typedef struct NextStateCtx {
	JNIEnv *env;
	jobject thisObj;
	int N;
} NextStateCtx;

JNIEXPORT void JNICALL Java_model_Model_load_1model(JNIEnv *env, jobject thisObj, jstring path) {
  	char* params[2];
  	params[0] = "pinswrapper";
  	params[1] = (*env)->GetStringUTFChars(env, path, NULL);

  	printf("Loading model from %s \n", params[1]);

  	model_t model = getModel(params);
  	lts_type_t ltstype = GBgetLTStype(model);
  	int N = (jint)lts_type_get_state_length(ltstype);
  	int K = (jint)dm_nrows(GBgetDMInfo(model));
  	
  	matrix_t* m = GBgetDMInfo(model);
	jclass intClass = (*env)->FindClass(env, "[I");
	jobjectArray DM = (*env)->NewObjectArray(env, K, intClass, NULL);
	for (int i = 0; i < K; i++) {
		int DMStateDep[N];
		for (int j = 0; j < N; j++) {
            DMStateDep[j] = dm_is_set(m, i, j);
        }
        jintArray stateDep = (*env)->NewIntArray(env, N);
        (*env)->SetIntArrayRegion(env, stateDep, 0, N, DMStateDep);
        (*env)->SetObjectArrayElement(env, DM, i, stateDep);
        (*env)->DeleteLocalRef(env, stateDep);
	}

	jclass cls = (*env)->GetObjectClass(env, thisObj);
    jfieldID model_t_fid = (*env)->GetFieldID(env, cls, "model_t_ptr", "J");
    jfieldID state_length_fid = (*env)->GetFieldID(env, cls, "stateLength", "I");
    jfieldID num_of_transtions_fid = (*env)->GetFieldID(env, cls, "numOfTransitions", "I");
    jfieldID dependency_matrix_fid = (*env)->GetFieldID(env, cls, "dependencyMatrix", "[[I");
    (*env)->SetLongField(env, thisObj, model_t_fid, (jlong)model);
    (*env)->SetIntField(env, thisObj, state_length_fid, (jint)N);
    (*env)->SetIntField(env, thisObj, num_of_transtions_fid, (jint)K);
    (*env)->SetObjectField(env, thisObj, dependency_matrix_fid, DM);

  	printf("Model loaded\n\n");
}

JNIEXPORT jintArray JNICALL Java_model_Model_get_1initial_1state
		(JNIEnv * env, jobject thisObj, jlong model_t_ptr){

    model_t model = (model_t)model_t_ptr;
  	lts_type_t ltstype = GBgetLTStype(model);
  	int N = lts_type_get_state_length(ltstype);

	int GB_initial_state[N];
	GBgetInitialState(model, GB_initial_state);

	jintArray initial_state = (jintArray)(*env)->NewIntArray(env, N);
	if(initial_state == NULL) {
    	return NULL;
  	}
	jint *int_ptr = calloc(N, sizeof(jint));
	if(int_ptr == NULL) {
		return NULL;
	}
	for(int i=0; i < N; i++) {
	    int_ptr[i] = GB_initial_state[i];
	}

	(*env)->SetIntArrayRegion(env,initial_state,0,N,(jint*) int_ptr);
 
	free(int_ptr);

	return initial_state;
}

void cb(NextStateCtx* ctx, transition_info_t *ti, int *dst, int *cpy){

	jintArray state = (*ctx->env)->NewIntArray(ctx->env, ctx->N);
    (*ctx->env)->SetIntArrayRegion(ctx->env, state, 0, ctx->N, dst);

    jclass cls = (*ctx->env)->GetObjectClass(ctx->env, ctx->thisObj);
    jmethodID mid = (*ctx->env)->GetMethodID(ctx->env, cls, "nextState", "([I)V");

    if (mid == 0) {
        return;
    }
    
	(*ctx->env)->CallVoidMethod(ctx->env, ctx->thisObj, mid, state);
}

JNIEXPORT jint JNICALL Java_model_Model_get_1next_1state
  	(JNIEnv *env, jobject thisObj, jlong model_t_ptr, jint transition, jintArray jstate){

  	int N = (*env)->GetArrayLength(env, jstate);
  	int* state = (*env)->GetIntArrayElements(env, jstate, 0);

  	NextStateCtx ctx = {env, thisObj, N};
	int c = GBgetTransitionsLong((model_t)model_t_ptr, transition, state, cb, &ctx);
  	return c;
}


/*void printstate(int* state,int N){
	printf("-----------\n");
	printf("next state:\n");
	for (int i = 0; i < N; ++i)
	{
		printf("%d", state[i]);
	}
	printf("\n-----------\n");
}*/

