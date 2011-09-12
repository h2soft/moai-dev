// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <aku/AKU-fmod.h>
#include <moaiext-fmod/MOAIFmod.h>
#include <moaiext-fmod/MOAIFmodChannel.h>
#include <moaiext-fmod/MOAIFmodSound.h>

//================================================================//
// AKU-fmod
//================================================================//

//----------------------------------------------------------------//
void AKUFmodInit () {

	MOAIFmod::Get ();
	
	REGISTER_LUA_CLASS ( MOAIFmod )
	REGISTER_LUA_CLASS ( MOAIFmodChannel )
	REGISTER_LUA_CLASS ( MOAIFmodSound )
}

//----------------------------------------------------------------//
void AKUFmodMuteSystem ( bool mute ) {
	
	MOAIFmod::Get().MuteChannels ( mute );
}

//----------------------------------------------------------------//
void AKUFmodRelease () {
	MOAIFmod::Get ().CloseSoundSystem ();
}

//----------------------------------------------------------------//
void AKUFmodRestoreSession () {
	#ifdef MOAI_OS_IPHONE
		FMOD_IPhone_RestoreAudioSession ();
	#endif
}

//----------------------------------------------------------------//
void AKUFmodUpdate () {

	MOAIFmod::Get ().Update ();
}
