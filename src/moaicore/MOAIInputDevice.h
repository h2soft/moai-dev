// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIINPUTDEVICE_H
#define MOAIINPUTDEVICE_H

class MOAISensor;

//================================================================//
// MOAIInputDevice
//================================================================//
/**	@brief	Manager class for input bindings.
*/
class MOAIInputDevice :
	public virtual USLuaObject {
private:

	STLString	mName;
	bool		mIsActive;

	USLeanArray < USRef < MOAISensor > > mSensors;

	//----------------------------------------------------------------//
	MOAISensor*		GetSensor			( u8 sensorID );

public:

	friend class MOAIInputMgr;

	DECL_LUA_FACTORY ( MOAIInputDevice )

	GET_SET ( STLString, Name, mName );
	GET_SET ( bool, Active, mIsActive );

	//----------------------------------------------------------------//
	void			HandleEvent			( u8 sensorID, USStream& eventStream );
					MOAIInputDevice		();
					~MOAIInputDevice	();
	void			RegisterLuaFuncs	( USLuaState& state );
	void			ReserveSensors		( u8 total );
	void			Reset				();
	void			SetSensor			( u8 sensorID, cc8* name, u32 type );
};

#endif
