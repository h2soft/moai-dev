// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef DISABLE_KAKAO

#include "pch.h"

#include <jni.h>

#include <moaiext-android/moaiext-jni.h>
#include <moaiext-android/MOAIKakaoLink.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//

int MOAIKakaoLink::_openKakaoLink ( lua_State* L ) {

	MOAILuaState state ( L );
	
	cc8* url = lua_tostring ( state, 1 );
	cc8* message = lua_tostring ( state, 2 );
	cc8* appId = lua_tostring ( state, 3 );
	cc8* appVer = lua_tostring ( state, 4 );
	cc8* appName = lua_tostring ( state, 5 );
	cc8* encoding = lua_tostring ( state, 6 );
	
	JNI_GET_ENV ( jvm, env );
	
	JNI_GET_JSTRING ( url, jurl );
	JNI_GET_JSTRING ( message, jmessage );
	JNI_GET_JSTRING ( appId, jappId );
	JNI_GET_JSTRING ( appVer, jappVer );
	JNI_GET_JSTRING ( appName, jappName );
	JNI_GET_JSTRING ( encoding, jencoding );
	
	jclass kakaoLink = env->FindClass ( "com/ziplinegames/moai/MoaiKakaoLink" );
    if ( kakaoLink == NULL ) {
	
		USLog::Print ( "MOAIKakaoLink: Unable to find java class %s", "com/ziplinegames/moai/MoaiKakaoLink" );
    } else {
	
    	jmethodID openKakaoLink = env->GetStaticMethodID ( kakaoLink, "openKakaoLink", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z" );
   		if ( openKakaoLink == NULL ) {
	
			USLog::Print ( "MOAIKakaoLink: Unable to find static java method %s", "openKakaoLink" );
		} else {
	
			jboolean jsuccess = ( jboolean )env->CallStaticBooleanMethod ( kakaoLink, openKakaoLink, jurl, jmessage, jappId, jappVer, jappName, jencoding);	
      lua_pushboolean ( state, jsuccess );
      return 1;
		}
	}

  lua_pushboolean ( state, false );		
	return 1;
}

//================================================================//
// MOAIKakaoLink
//================================================================//

//----------------------------------------------------------------//
MOAIKakaoLink::MOAIKakaoLink () {

	RTTI_SINGLE ( MOAILuaObject )	
}

//----------------------------------------------------------------//
MOAIKakaoLink::~MOAIKakaoLink () {

}

//----------------------------------------------------------------//
void MOAIKakaoLink::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "openKakaoLink", _openKakaoLink },		
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

#endif