// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <jni.h>

#include <moaiext-android/moaiext-jni.h>
#include <moaiext-android/MOAITstoreBilling.h>

extern JavaVM* jvm;

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name	setApplicationId
*/
int MOAITstoreBilling::_setApplicationId ( lua_State* L ) {
	
	MOAILuaState state ( L );	
	
	cc8* appId = lua_tostring ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );

	JNI_GET_JSTRING ( appId, jappId );

	jclass tstore = env->FindClass ( "com/ziplinegames/moai/MoaiTstoreBilling" );
	if ( tstore == NULL ) {
	
		USLog::Print ( "MOAITStoreBilling: Unable to find java class %s", "com/ziplinegames/moai/MoaiTstoreBilling" );
	} else {
	
		jmethodID setApplicationId = env->GetStaticMethodID ( tstore, "setApplicationId", "(Ljava/lang/String;)V" );
		if ( setApplicationId == NULL ) {
	
			USLog::Print ( "MOAITStoreBilling: Unable to find static java method %s", "setApplicationId" );
		} else {
	
			env->CallStaticVoidMethod ( tstore, setApplicationId, jappId );		
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	requestPurchase
*/
int MOAITstoreBilling::_requestPurchase ( lua_State* L ) {
	
	MOAILuaState state ( L );	
	
	cc8* productId = lua_tostring ( state, 1 );
	
	JNI_GET_ENV ( jvm, env );

	JNI_GET_JSTRING ( productId, jproductId );

	jclass tstore = env->FindClass ( "com/ziplinegames/moai/MoaiTstoreBilling" );
	if ( tstore == NULL ) {
	
		USLog::Print ( "MOAITStoreBilling: Unable to find java class %s", "com/ziplinegames/moai/MoaiTstoreBilling" );
	} else {
	
		jmethodID requestPurchase = env->GetStaticMethodID ( tstore, "requestPurchase", "(Ljava/lang/String;)V" );
		if ( requestPurchase == NULL ) {
	
			USLog::Print ( "MOAITStoreBilling: Unable to find static java method %s", "requestPurchase" );
		} else {
	
			env->CallStaticVoidMethod ( tstore, requestPurchase, jproductId );		
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
int MOAITstoreBilling::_setListener ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	u32 idx = state.GetValue < u32 >( 1, TOTAL );

	if ( idx < TOTAL ) {
		
		MOAITstoreBilling::Get ().mListeners [ idx ].SetStrongRef ( state, 2 );
	}
	
	return 0;
}

//================================================================//
// MOAITstoreBilling
//================================================================//

//----------------------------------------------------------------//
MOAITstoreBilling::MOAITstoreBilling () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAITstoreBilling::~MOAITstoreBilling () {
}

//----------------------------------------------------------------//
void MOAITstoreBilling::RegisterLuaClass ( MOAILuaState& state ) {

	state.SetField ( -1, "PURCHASE_COMPLETE",	( u32 )PURCHASE_COMPLETE );
	state.SetField ( -1, "PURCHASE_CANCEL",	( u32 )PURCHASE_CANCEL );
	state.SetField ( -1, "PURCHASE_ERROR",	( u32 )PURCHASE_ERROR );

	luaL_Reg regTable [] = {
		{ "setApplicationId",	_setApplicationId },
		{ "requestPurchase",	_requestPurchase },
		{ "setListener",	_setListener },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

void MOAITstoreBilling::NotifyPurchaseComplete ( ) {
	
	MOAILuaRef& callback = this->mListeners [ PURCHASE_COMPLETE ];

	if ( callback ) {
	
		MOAILuaStateHandle state = callback.GetSelf ();
	
		state.DebugCall ( 0, 0 );
	}
}

void MOAITstoreBilling::NotifyPurchaseCancel ( ) {
	
	MOAILuaRef& callback = this->mListeners [ PURCHASE_CANCEL ];

	if ( callback ) {
	
		MOAILuaStateHandle state = callback.GetSelf ();
	
		state.DebugCall ( 0, 0 );
	}
}


void MOAITstoreBilling::NotifyPurchaseError ( int errorCode, int subErrorCode ) {
	
	MOAILuaRef& callback = this->mListeners [ PURCHASE_ERROR ];

	if ( callback ) {
	
		MOAILuaStateHandle state = callback.GetSelf ();
	
		lua_pushinteger ( state, errorCode );	
		lua_pushinteger ( state, subErrorCode );
		
		state.DebugCall ( 2, 0 );
		
	}
}


//================================================================//
// Tstore JNI methods
//================================================================//

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiTstoreBilling_AKUNotifyTstorePurchaseComplete ( JNIEnv* env, jclass obj ) {
	
	MOAITstoreBilling::Get ().NotifyPurchaseComplete ( );
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiTstoreBilling_AKUNotifyTstorePurchaseCancel ( JNIEnv* env, jclass obj ) {

	MOAITstoreBilling::Get ().NotifyPurchaseCancel ( );
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiTstoreBilling_AKUNotifyTstorePurchaseError ( JNIEnv* env, jclass obj, jint errorCode, jint subErrorCode ) {

	MOAITstoreBilling::Get ().NotifyPurchaseError ( errorCode, subErrorCode );
}
