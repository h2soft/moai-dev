//----------------------------------------------------------------//
// Copyright (c) 2012 H2SOFT Co., Ltd
// All Rights Reserved. 
// http://www.h2soft.kr
//----------------------------------------------------------------//
#include "pch.h"

#include <jni.h>

#include <moaiext-android/moaiext-jni.h>
#include <moaiext-android/MOAIAdMobAndroid.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//
//----------------------------------------------------------------//
/**	@name	showBanner
	@text	Show AdMob banner.
			
	@in		string	adUnitId 
	@out 	nil
*/
int MOAIAdMobAndroid::_showBanner ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* adUnitId = lua_tostring ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( adUnitId, jadUnitId );

	jclass admob = env->FindClass ( "com/ziplinegames/moai/MoaiAdMob" );
	if ( admob == NULL ) {
	
		USLog::Print ( "MOAIAdMobAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiAdMob" );
	} else {
	
		jmethodID showBanner = env->GetStaticMethodID ( admob, "showBanner", "(Ljava/lang/String;)V" );
		if ( showBanner == NULL ) {
	
			USLog::Print ( "MOAIAdMobAndroid: Unable to find static java method %s", "showBanner" );
		} else {
	
			env->CallStaticVoidMethod ( admob, showBanner, jadUnitId );		
		}
	}
	return 0;
}

//----------------------------------------------------------------//
/**	@name	dismiss
	@text	Dismiss AdMob banner.
			
	@in		nil
	@out 	nil
*/
int MOAIAdMobAndroid::_dismiss ( lua_State* L ) {
	
	JNI_GET_ENV ( jvm, env );
	
	jclass admob = env->FindClass ( "com/ziplinegames/moai/MoaiAdMob" );
	if ( admob == NULL ) {	
		USLog::Print ( "MOAIAdMobAndroid: Unable to find java class %s", "com/ziplinegames/moai/MoaiAdMob" );
	} else {
	
		jmethodID dismiss = env->GetStaticMethodID ( admob, "dismiss", "()V" );
		if ( dismiss == NULL ) {
	
			USLog::Print ( "MOAIAdMobAndroid: Unable to find static java method %s", "dismiss" );
		} else {
	
			env->CallStaticVoidMethod ( admob, dismiss );		
		}
	}
	return 0;
}

//================================================================//
// MOAIAdMobAndroid
//================================================================//

//----------------------------------------------------------------//
MOAIAdMobAndroid::MOAIAdMobAndroid () {

	RTTI_SINGLE ( MOAILuaObject )	
}

//----------------------------------------------------------------//
MOAIAdMobAndroid::~MOAIAdMobAndroid () {

}

//----------------------------------------------------------------//
void MOAIAdMobAndroid::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "showBanner",	_showBanner },
		{ "dismiss",		_dismiss },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
