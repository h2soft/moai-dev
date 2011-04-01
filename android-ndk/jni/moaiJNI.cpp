#include <jni.h>
#include <time.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "chipmunk.h"
#include <aku/AKU.h>
#include "USLog.cpp"


JavaVM *jvm;
jobject javaObject;
AKUContextID mAku;

jmethodID m_AKUEnterFullscreenModeFunc;
jmethodID m_AKUExitFullscreenModeFunc;
jmethodID m_AKUHideLoadingScreenFunc;
jmethodID m_AKUOpenWindowFunc;
jmethodID m_AKUShowLoadingScreenFunc;
jmethodID m_AKUShowSoftwareKeyboardFunc;
jmethodID m_AKUStartGameLoopFunc;

#define IMPORTGL_NO_FNPTR_DEFS
#define IMPORTGL_API
#define IMPORTGL_FNPTRINIT = NULL


/* Imports function pointers to selected function calls in OpenGL ES Common
 * or Common Lite profile DLL or shared object. The function pointers are
 * stored as global symbols with equivalent function name but prefixed with
 * "funcPtr_". Standard gl/egl calls are redirected to the function pointers
 * with preprocessor macros (see importgl.h).
 */
int importGLInit()
{
    int result = 1;

#ifndef DISABLE_IMPORTGL

#undef IMPORT_FUNC

sGLESSO = dlopen("libGLESv1_CM.so", RTLD_NOW);

if (sGLESSO == NULL)
    return 0;   // Cannot find OpenGL ES Common or Common Lite SO.

#define IMPORT_FUNC(funcName) do { \
    void *procAddress = (void *)dlsym(sGLESSO, #funcName); \
    if (procAddress == NULL) result = 0; \
    *((void **)&FNPTR(funcName)) = procAddress; } while (0)

    IMPORT_FUNC(glBlendFunc);
    IMPORT_FUNC(glClear);
    IMPORT_FUNC(glClearColorx);
    IMPORT_FUNC(glColor4x);
    IMPORT_FUNC(glColorPointer);
    IMPORT_FUNC(glDisable);
    IMPORT_FUNC(glDisableClientState);
    IMPORT_FUNC(glDrawArrays);
    IMPORT_FUNC(glEnable);
    IMPORT_FUNC(glEnableClientState);
    IMPORT_FUNC(glFrustumx);
    IMPORT_FUNC(glGetError);
    IMPORT_FUNC(glLightxv);
    IMPORT_FUNC(glLoadIdentity);
    IMPORT_FUNC(glMaterialx);
    IMPORT_FUNC(glMaterialxv);
    IMPORT_FUNC(glMatrixMode);
    IMPORT_FUNC(glMultMatrixx);
    IMPORT_FUNC(glNormalPointer);
    IMPORT_FUNC(glPopMatrix);
    IMPORT_FUNC(glPushMatrix);
    IMPORT_FUNC(glRotatex);
    IMPORT_FUNC(glScalex);
    IMPORT_FUNC(glShadeModel);
    IMPORT_FUNC(glTranslatex);
    IMPORT_FUNC(glVertexPointer);
    IMPORT_FUNC(glViewport);

#endif /* DISABLE_IMPORTGL */

    return result;
}


void importGLDeinit()
{
#ifndef DISABLE_IMPORTGL
#ifdef LINUX
    dlclose(sGLESSO);
#endif
#endif /* DISABLE_IMPORTGL */
}

// -----------------------------

namespace MoaiInputDeviceID {
	enum {
		DEVICE,
		TOTAL,
	};
}

namespace MoaiInputDeviceSensorID {
	enum {
		COMPASS,
		LEVEL,
		LOCATION,
		TOUCH,
		TOTAL,
	};
}



//================================================================//
// AKU callbacks
//================================================================//

//----------------------------------------------------------------//
void _AKUEnterFullscreenModeFunc () {

	 __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Enter Full Screen Callback Start.");
	JNIEnv *env;

	if(jvm == NULL)
		return;

	
	jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(env == NULL)
		return;


	  if(m_AKUStartGameLoopFunc == NULL)
	  {
		  __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Enter Full Screen Callback FAILURE.");
	  }

     env->CallVoidMethod(javaObject, m_AKUEnterFullscreenModeFunc);
}

//----------------------------------------------------------------//
void _AKUExitFullscreenModeFunc () {

	 __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Exit Full Screen Callback Start.");
	JNIEnv *env;

	if(jvm == NULL)
		return;

	
	jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(env == NULL)
		return;


	  if(m_AKUStartGameLoopFunc == NULL)
	  {
		  __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Exit Full Screen Callback FAILURE.");
	  }

     env->CallVoidMethod(javaObject, m_AKUExitFullscreenModeFunc);

}

//----------------------------------------------------------------//
void _AKUHideLoadingScreenFunc () {
	
	 __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Hide Loading Screen Callback Start.");
	JNIEnv *env;

	if(jvm == NULL)
		return;

	
	jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(env == NULL)
		return;


	  if(m_AKUStartGameLoopFunc == NULL)
	  {
		  __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Hide Loading Screen Callback FAILURE.");
	  }

     env->CallVoidMethod(javaObject, m_AKUHideLoadingScreenFunc);
}

//----------------------------------------------------------------//
void _AKUOpenWindowFunc ( const char* title, int width, int height ) {
}

//----------------------------------------------------------------//
void _AKUShowLoadingScreenFunc () {

	 __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Show Loading Screen Callback Start.");
	JNIEnv *env;

	if(jvm == NULL)
		return;

	
	jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(env == NULL)
		return;


	  if(m_AKUStartGameLoopFunc == NULL)
	  {
		  __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Show Loading Screen Callback FAILURE.");
	  }

     env->CallVoidMethod(javaObject, m_AKUShowLoadingScreenFunc);
}

//----------------------------------------------------------------//
void _AKUShowSoftwareKeyboardFunc () {

	 __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Software Keyboard Callback Start.");
	JNIEnv *env;

	if(jvm == NULL)
		return;

	
	jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(env == NULL)
		return;


	  if(m_AKUStartGameLoopFunc == NULL)
	  {
		  __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Software Keyboard Callback FAILURE.");
	  }
	
     env->CallVoidMethod(javaObject, m_AKUShowSoftwareKeyboardFunc);
}

//----------------------------------------------------------------//
void _AKUStartGameLoopFunc () {
	
	 __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Game Loop Callback Start.");
	JNIEnv *env;

	if(jvm == NULL)
		return;

	
	jvm->GetEnv((void**)&env, JNI_VERSION_1_4);

	if(env == NULL)
		return;


	  if(m_AKUStartGameLoopFunc == NULL)
	  {
		  __android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Game Loop Callback FAILURE.");
	  }

     env->CallVoidMethod(javaObject, m_AKUStartGameLoopFunc);


}
// -------------------------------------------------------------//
void _DrawView()
{
}

int JNI_OnLoad(JavaVM* vm, void* reserved)
{
    jvm = vm;
	
	return JNI_VERSION_1_4;
}

extern "C"
void Java_com_moai_MoaiView_RestartAku
(JNIEnv *env, jclass clazz, jobject thizz) 
{
	jclass classic = env->GetObjectClass(javaObject);

	mAku = AKUCreateContext ();
		
	AKUSetInputConfigurationName ( "Android" );

	AKUReserveInputDevices			( MoaiInputDeviceID::TOTAL );
	AKUSetInputDevice				( MoaiInputDeviceID::DEVICE, "device" );
		
	AKUReserveInputDeviceSensors	( MoaiInputDeviceID::DEVICE, MoaiInputDeviceSensorID::TOTAL );
	AKUSetInputDeviceCompass		( MoaiInputDeviceID::DEVICE, MoaiInputDeviceSensorID::COMPASS,		"compass" );
	AKUSetInputDeviceLevel			( MoaiInputDeviceID::DEVICE, MoaiInputDeviceSensorID::LEVEL,		"level" );
	AKUSetInputDeviceLocation		( MoaiInputDeviceID::DEVICE, MoaiInputDeviceSensorID::LOCATION,		"location" );
	AKUSetInputDeviceTouch			( MoaiInputDeviceID::DEVICE, MoaiInputDeviceSensorID::TOUCH,		"touch" );
		
	AKUSetFunc_EnterFullscreenMode ( _AKUEnterFullscreenModeFunc );
	AKUSetFunc_ExitFullscreenMode ( _AKUExitFullscreenModeFunc );
	AKUSetFunc_OpenWindow ( _AKUOpenWindowFunc );
	AKUSetFunc_StartGameLoop ( _AKUStartGameLoopFunc );

	m_AKUEnterFullscreenModeFunc  = env->GetMethodID(classic,"AKUEnterFullscreenModeFunc", "()V");
	m_AKUExitFullscreenModeFunc  = env->GetMethodID(classic,"AKUExitFullscreenModeFunc", "()V");
	m_AKUHideLoadingScreenFunc  = env->GetMethodID(classic,"AKUHideLoadingScreenFunc", "()V");
	//m_AKUOpenWindowFunc;
	m_AKUShowLoadingScreenFunc  = env->GetMethodID(classic,"AKUShowLoadingScreenFunc", "()V");
	m_AKUShowSoftwareKeyboardFunc  = env->GetMethodID(classic,"AKUShowSoftwareKeyboardFunc", "()V");
	m_AKUStartGameLoopFunc = env->GetMethodID(classic,"AKUStartGameLoopFunc", "()V");

	__android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Aku Successfully Initialized");
}
extern "C"
void Java_com_moai_MoaiView_InitializeAku
  (JNIEnv *env, jclass clazz, jobject thizz) 
{

	importGLInit();

    glDisable(GL_CULL_FACE);
  
	javaObject = (jobject)env->NewGlobalRef(thizz);
	
	Java_com_moai_MoaiView_RestartAku(env, clazz, thizz);
	
}

extern "C"
void Java_com_moai_MoaiView_Run
	(JNIEnv *env, jclass clazz, jstring fileName)
{
	__android_log_write(ANDROID_LOG_ERROR,"MoaiJNI","Entering Run Func");
	char buf[512];
    const char *str;
    str = env->GetStringUTFChars(fileName, NULL);
     if (str == NULL) {
         return; /* OutOfMemoryError already thrown */
     }


	 strcpy(buf, str);
    env->ReleaseStringUTFChars(fileName, str);


	AKUSetContext ( mAku );
	AKURunScript (buf);
	
}
extern "C"
void Java_com_moai_MoaiView_FinalizeAku
	(JNIEnv *env, jclass clazz)
{
	AKUFinalize();
}
extern "C"
void Java_com_moai_MoaiView_DeinitializeAku
(JNIEnv *env, jclass clazz)
{
	AKUDeleteContext ( mAku );
	importGLDeinit();
}
extern "C"
void Java_com_moai_MoaiView_onDraw
	(JNIEnv *env, jclass clazz,
	 jint width, jint height)
{
	AKUSetContext(mAku);
	AKUResize(width, height);
	AKURender();
}
extern "C"
void Java_com_moai_MoaiView_onUpdateAnim
	(JNIEnv *env, jclass clazz)
{
	
	AKUSetContext ( mAku );
	AKUUpdate ();
	//_DrawView();
}
extern "C"
void Java_com_moai_MoaiView_onUpdateHeading
(JNIEnv *env, jclass clazz, jint heading)
{
	
		AKUEnqueueCompassEvent (
			MoaiInputDeviceID::DEVICE,
			MoaiInputDeviceSensorID::COMPASS,
			heading
		);
}
extern "C"	
void Java_com_moai_MoaiView_onUpdateLocation
(JNIEnv *env, jclass clazz, jint longitude, jint latitude, jint altitude,
jfloat hAccuracy, jfloat vAccuracy, jfloat speed )
{
	
		AKUEnqueueLocationEvent (
			MoaiInputDeviceID::DEVICE,
			MoaiInputDeviceSensorID::LOCATION,
			longitude,
			latitude,
			altitude,
			hAccuracy,
			vAccuracy,
			speed
		);
}
extern "C"
void Java_com_moai_MoaiView_handleTouches
(JNIEnv *env, jclass clazz, jint touch, jboolean down, jint locX, jint locY, jint tapCount)
{
			AKUEnqueueTouchEvent (
				MoaiInputDeviceID::DEVICE,
				MoaiInputDeviceSensorID::TOUCH,
				touch,
				down,
				locX,
				locY,
				tapCount
			);
		
}

extern "C"
void Java_com_moai_MoaiView_setWorkingDirectory
(JNIEnv *env, jclass clazz, jstring path)
{
	char buf[512];
    const char *str;
    str = env->GetStringUTFChars(path, NULL);
     if (str == NULL) {
         return; /* OutOfMemoryError already thrown */
     }
	 strcpy(buf, str);
    env->ReleaseStringUTFChars(path, str);
	USFileSys::SetCurrentPath(buf);
	USLuaRuntime::Get().SetPath(buf);
}


