// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"

#include <moaicore/MOAIButtonSensor.h>
#include <moaicore/MOAICompassSensor.h>
#include <moaicore/MOAIInputDevice.h>
#include <moaicore/MOAIInputMgr.h>
#include <moaicore/MOAIJoystickSensor.h>
#include <moaicore/MOAIKeyboardSensor.h>
#include <moaicore/MOAILevelSensor.h>
#include <moaicore/MOAILocationSensor.h>
#include <moaicore/MOAIPointerSensor.h>
#include <moaicore/MOAISensor.h>
#include <moaicore/MOAITouchSensor.h>

#define LUAVAR_DEVICES			"devices"
#define LUAVAR_CONFIGURATION	"configuration"

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//

//================================================================//
// MOAIInputMgr
//================================================================//

//----------------------------------------------------------------//
bool MOAIInputMgr::CheckSensor ( u8 deviceID, u8 sensorID, u32 type ) {

	MOAIInputDevice* device = this->GetDevice ( deviceID );
	if ( device && device->mIsActive ) {
		MOAISensor* sensor = device->GetSensor ( sensorID );
		return ( sensor && ( sensor->mType == type ));
	}
	return false;
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueButtonEvent ( u8 deviceID, u8 sensorID, bool down ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::BUTTON )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::BUTTON );
		MOAIButtonSensor::WriteEvent ( this->mInput, down );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueCompassEvent ( u8 deviceID, u8 sensorID, float heading ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::COMPASS )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::COMPASS );
		MOAICompassSensor::WriteEvent ( this->mInput, heading );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueKeyboardEvent ( u8 deviceID, u8 sensorID, u32 keyID, bool down ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::KEYBOARD )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::KEYBOARD );
		MOAIKeyboardSensor::WriteEvent ( this->mInput, keyID, down );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueLevelEvent ( u8 deviceID, u8 sensorID, float x, float y, float z ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::LEVEL )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::LEVEL );
		MOAILevelSensor::WriteEvent ( this->mInput, x, y, z );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueLocationEvent ( u8 deviceID, u8 sensorID, double longitude, double latitude, double altitude, float hAccuracy, float vAccuracy, float speed ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::LOCATION )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::LOCATION );
		MOAILocationSensor::WriteEvent ( this->mInput, longitude, latitude, altitude, hAccuracy, vAccuracy, speed );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueuePointerEvent ( u8 deviceID, u8 sensorID, int x, int y ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::POINTER )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::POINTER );
		MOAIPointerSensor::WriteEvent ( this->mInput, x, y );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueTouchEvent ( u8 deviceID, u8 sensorID, u32 touchID, bool down, float x, float y, u32 tapCount ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::TOUCH )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::TOUCH );
		MOAITouchSensor::WriteEvent ( this->mInput, touchID, down, x, y, tapCount );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::EnqueueTouchEventCancel ( u8 deviceID, u8 sensorID ) {

	if ( this->CheckSensor ( deviceID, sensorID, MOAISensor::TOUCH )) {
		this->WriteEventHeader ( deviceID, sensorID, MOAISensor::TOUCH );
		MOAITouchSensor::WriteEventCancel ( this->mInput );
	}
}

//----------------------------------------------------------------//
MOAIInputDevice* MOAIInputMgr::GetDevice ( u8 deviceID ) {

	if ( deviceID < this->mDevices.Size ()) {
		return this->mDevices [ deviceID ];
	}
	return 0;
}

//----------------------------------------------------------------//
MOAISensor* MOAIInputMgr::GetSensor ( u8 deviceID, u8 sensorID ) {

	MOAIInputDevice* device = this->GetDevice ( deviceID );
	if ( device ) {
		return device->GetSensor ( sensorID );
	}
	return 0;
}

//----------------------------------------------------------------//
MOAIInputMgr::MOAIInputMgr () {
	
	RTTI_SINGLE ( USLuaData )
	
	this->mInput.SetChunkSize ( 1024 );
}

//----------------------------------------------------------------//
MOAIInputMgr::~MOAIInputMgr () {
}

//----------------------------------------------------------------//
void MOAIInputMgr::RegisterLuaClass ( USLuaState& state ) {
	UNUSED ( state );

	//lua_newtable ( state );
	//lua_setfield ( state, -2, LUAVAR_DEVICES );
}

//----------------------------------------------------------------//
void MOAIInputMgr::ReserveDevices ( u8 total ) {

	this->mDevices.Resize ( total );
}

//----------------------------------------------------------------//
void MOAIInputMgr::ReserveSensors ( u8 deviceID, u8 total ) {

	MOAIInputDevice* device = this->GetDevice ( deviceID );
	if ( device ) {
		device->ReserveSensors ( total );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::Reset () {

	for ( u32 i = 0; i < this->mDevices.Size (); ++i ) {
		MOAIInputDevice* device = this->mDevices [ i ];
		if ( device ) {
			device->Reset ();
		}
	}
	
	this->mInput.Seek ( 0, SEEK_SET );
}

//----------------------------------------------------------------//
void MOAIInputMgr::SetConfigurationName ( cc8* name ) {

	USLuaStateHandle state = USLuaRuntime::Get ().State ();
	this->PushLuaClass ( state );
	
	state.SetField ( -1, LUAVAR_CONFIGURATION, name );
}

//----------------------------------------------------------------//
void MOAIInputMgr::SetDevice ( u8 deviceID, cc8* name ) {

	MOAIInputDevice* device = new MOAIInputDevice ();
	
	device->SetName ( name );

	this->mDevices.Grow ( deviceID + 1 );
	this->mDevices [ deviceID ] = device;
	
	USLuaStateHandle state = USLuaRuntime::Get ().State ();
	this->PushLuaClass ( state );
	
	//if ( state.GetFieldWithType ( -1, LUAVAR_DEVICES, LUA_TTABLE )) {
		device->PushLuaInstance ( state );
		lua_setfield ( state, -2, name );
	//}
}

//----------------------------------------------------------------//
void MOAIInputMgr::SetDeviceActive ( u8 deviceID, bool active ) {

	MOAIInputDevice* device = this->GetDevice ( deviceID );
	if ( device ) {
		device->SetActive ( active );
	}
}

//----------------------------------------------------------------//
void MOAIInputMgr::SetSensor ( u8 deviceID, u8 sensorID, cc8* name, u32 type ) {

	MOAIInputDevice* device = this->GetDevice ( deviceID );
	if ( device ) {
		device->SetSensor ( sensorID, name, type );
	}
}

//----------------------------------------------------------------//
STLString MOAIInputMgr::ToString () {

	STLString repr;
	return repr;
}

//----------------------------------------------------------------//
void MOAIInputMgr::Update () {

	u32 total = this->mInput.GetCursor ();
	this->Reset ();
	
	while ( this->mInput.GetCursor () < total ) {
	
		u8 deviceID		= this->mInput.Read < u8 >();
		u8 sensorID		= this->mInput.Read < u8 >();
		//u32 type		= ( u32 )this->mInput.Read < u8 >();
		this->mInput.Read < u8 >();
		
		MOAISensor* sensor = this->GetSensor ( deviceID, sensorID );
		sensor->HandleEvent ( this->mInput );
	}
	this->mInput.Seek ( 0, SEEK_SET );
}

//----------------------------------------------------------------//
void MOAIInputMgr::WriteEventHeader ( u8 deviceID, u8 sensorID, u32 type ) {

	this->mInput.Write < u8 >(( u8 )deviceID );
	this->mInput.Write < u8 >(( u8 )sensorID );
	this->mInput.Write < u8 >(( u8 )type );
}
