// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <chipmunk/chipmunk.h>
#include <moaicore/MOAICp.h>

SUPPRESS_EMPTY_FILE_WARNING
#if USE_CHIPMUNK

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@name getBiasCoefficient
	@param1 self @type userdata
	@text Returns the current bias coefficient.
	@return The bias coefficient. @type number
*/
int MOAICp::_getBiasCoefficient ( lua_State* L ) {
	
	lua_pushnumber ( L, cp_bias_coef );
	return 1;
}

//----------------------------------------------------------------//
/**	@name getCollisionSlop
	@param1 self @type userdata
	@text Returns the current collision slop.
	@return The collision slop. @type number
*/
int MOAICp::_getCollisionSlop ( lua_State* L ) {
	
	lua_pushnumber ( L, cp_collision_slop );
	return 1;
}

//----------------------------------------------------------------//
/**	@name getContactPersistence
	@param1 self @type userdata
	@text Returns the current contact persistence.
	@return The contact persistence. @type number
*/
int MOAICp::_getContactPersistence ( lua_State* L ) {

	lua_pushnumber ( L, cp_contact_persistence );
	return 1;
}

//----------------------------------------------------------------//
/**	@name setBiasCoefficient
	@param1 self @type userdata
	@param2 bias @type number
	@text Sets the bias coefficient.
	@return nil
*/
int MOAICp::_setBiasCoefficient ( lua_State* L ) {
	USLuaState state ( L );
	
	cp_bias_coef =	state.GetValue < cpFloat >( 1, cp_bias_coef );
	return 0;
}

//----------------------------------------------------------------//
/**	@name setCollisionSlop
	@param1 self @type userdata
	@param2 slop @type number
	@text Sets the collision slop.
	@return nil
*/
int MOAICp::_setCollisionSlop ( lua_State* L ) {
	USLuaState state ( L );
	
	cp_collision_slop =	state.GetValue < cpFloat >( 1, cp_collision_slop );
	return 0;
}

//----------------------------------------------------------------//
/**	@name setCollisionSlop
	@param1 self @type userdata
	@param2 persistance @type number
	@text Sets the contact persistance.
	@return nil
*/
int MOAICp::_setContactPersistence ( lua_State* L ) {
	USLuaState state ( L );
	
	cp_contact_persistence =	state.GetValue < cpTimestamp >( 1, cp_contact_persistence );
	return 0;
}

//================================================================//
// MOAICp
//================================================================//

//----------------------------------------------------------------//
MOAICp::MOAICp () {

	RTTI_SINGLE ( USLuaObject )
}

//----------------------------------------------------------------//
MOAICp::~MOAICp () {
}

//----------------------------------------------------------------//
void MOAICp::RegisterLuaClass ( USLuaState& state ) {

	state.SetField ( -1, "INFINITY",	INFINITY );

	luaL_Reg regTable[] = {
		{ "getBiasCoefficient",		_getBiasCoefficient },
		{ "getCollisionSlop",		_getCollisionSlop },
		{ "getContactPersistence",	_getContactPersistence },
		{ "setBiasCoefficient",		_setBiasCoefficient },
		{ "setCollisionSlop",		_setCollisionSlop },
		{ "setContactPersistence",	_setContactPersistence },
		{ NULL, NULL }
	};

	luaL_register( state, 0, regTable );
}

#endif