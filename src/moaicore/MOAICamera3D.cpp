// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAICamera3D.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAIViewport.h>

#define DEFAULT_HFOV 60.0f
#define DEFAULT_NEAR_PLANE 1.0f
#define DEFAULT_FAR_PLANE 10000.0f

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	getFarPlane
	@text	Returns the camera's far plane.

	@in		MOAICamera3D self
	@out	number far
*/
int MOAICamera3D::_getFarPlane ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICamera3D, "U" )
	lua_pushnumber ( state, self->mFarPlane );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getHFOV
	@text	Returns the camera's horizontal field of view.

	@in		MOAICamera3D self
	@out	number hfov
*/
int MOAICamera3D::_getHFOV ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICamera3D, "U" )
	lua_pushnumber ( state, self->mHFOV );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getNearPlane
	@text	Returns the camera's near plane.

	@in		MOAICamera3D self
	@out	number near
*/
int MOAICamera3D::_getNearPlane ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICamera3D, "U" )
	lua_pushnumber ( state, self->mNearPlane );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFarPlane
	@text	Sets the camera's far plane distance.

	@in		MOAICamera3D self
	@opt	number far			Default value is 10000.
	@out	nil
*/
int MOAICamera3D::_setFarPlane ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICamera3D, "U" )
	self->mFarPlane = state.GetValue < float >( 2, DEFAULT_FAR_PLANE );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setHFOV
	@text	Sets the camera's horizontal field of view.

	@in		MOAICamera3D self
	@opt	number hfow			Default value is 60.
	@out	nil
*/
int MOAICamera3D::_setHFOV ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICamera3D, "U" )
	self->mHFOV = state.GetValue < float >( 2, DEFAULT_HFOV );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setNearPlane
	@text	Sets the camera's near plane distance.

	@in		MOAICamera3D self
	@opt	number near			Default value is 1.
	@out	nil
*/
int MOAICamera3D::_setNearPlane ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAICamera3D, "U" )
	self->mNearPlane = state.GetValue < float >( 2, DEFAULT_NEAR_PLANE );
	return 0;
}

//================================================================//
// MOAICamera3D
//================================================================//

//----------------------------------------------------------------//
USMatrix4x4 MOAICamera3D::GetProjMtx ( const MOAIViewport& viewport ) const {
	UNUSED ( viewport );
	
	// do the camera translation
	float xs = Cot (( this->mHFOV * ( float )D2R ) / 2.0f );
	float ys = xs * viewport.GetAspect ();

	USMatrix4x4 mtx;
	mtx.Perspective ( xs, ys, this->mNearPlane, this->mFarPlane );
	
	return mtx;
}

//----------------------------------------------------------------//
USMatrix4x4 MOAICamera3D::GetProjMtxInv ( const MOAIViewport& viewport ) const {
	UNUSED ( viewport );

	USMatrix4x4 mtx;
	mtx.Ident ();
	return mtx;
}

//----------------------------------------------------------------//
MOAICamera3D::MOAICamera3D () :
	mHFOV ( DEFAULT_HFOV ),
	mNearPlane ( DEFAULT_NEAR_PLANE ),
	mFarPlane ( DEFAULT_FAR_PLANE ) {

	RTTI_SINGLE ( MOAICamera )
}

//----------------------------------------------------------------//
MOAICamera3D::~MOAICamera3D () {
}

//----------------------------------------------------------------//
void MOAICamera3D::RegisterLuaClass ( MOAILuaState& state ) {
	MOAICamera::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAICamera3D::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAICamera::RegisterLuaFuncs ( state );

	luaL_Reg regTable [] = {
		{ "getFarPlane",		_getFarPlane },
		{ "getHFOV",			_getHFOV },
		{ "getNearPlane",		_getNearPlane },
		{ "setFarPlane",		_setFarPlane },
		{ "setHFOV",			_setHFOV },
		{ "setNearPlane",		_setNearPlane },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
