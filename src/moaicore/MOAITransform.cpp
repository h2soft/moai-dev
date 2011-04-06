// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAITransform.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	addLoc
	@text	Adds a delta to the transform's location.
	
	@in		MOAITransform self
	@in		number xDelta
	@in		number yDelta
	@out	nil
*/
int MOAITransform::_addLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )
	
	USVec2D loc = self->GetLoc ();
	
	loc.mX += state.GetValue < float >( 2, 0.0f );
	loc.mY += state.GetValue < float >( 3, 0.0f );
	
	self->SetLoc ( loc );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	addRot
	@text	Adds a delta to the transform's rotation
	
	@in		MOAITransform self
	@in		number rDelta		In degrees.
	@out	nil
*/
int MOAITransform::_addRot ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UN" )
	
	float d = self->GetRot ();
	d += state.GetValue < float >( 2, 0.0f );
	
	self->SetRot ( d );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	addScl
	@text	Adds a delta to the transform's scale
	
	@in		MOAITransform self
	@in		number xSclDelta
	@in		number ySclDelta
	@out	nil
*/
int MOAITransform::_addScl ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )
	
	USVec2D scl = self->GetScl ();
	
	scl.mX += state.GetValue < float >( 2, 0.0f );
	scl.mY += state.GetValue < float >( 3, 0.0f );
	
	self->SetScl ( scl );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getLoc
	@text	Returns the transform's current location.
	
	@in		MOAITransform self
	@out	number xLoc
	@out	number yLoc
*/
int	MOAITransform::_getLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "U" )
	
	lua_pushnumber ( state, self->mLoc.mX );
	lua_pushnumber ( state, self->mLoc.mY );

	return 2;
}

//----------------------------------------------------------------//
/**	@name	getRot
	@text	Returns the transform's current rotation.
	
	@in		MOAITransform self
	@out	number rot			Rotation in degrees.
*/
int	MOAITransform::_getRot ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "U" )
	
	lua_pushnumber ( state, self->mDegrees );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	getScl
	@text	Returns the transform's current scale.
	
	@in		MOAITransform self
	@out	number xScl
	@out	number yScl
*/
int	MOAITransform::_getScl ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "U" )
	
	lua_pushnumber ( state, self->mScale.mX );
	lua_pushnumber ( state, self->mScale.mY );

	return 2;
}

//----------------------------------------------------------------//
/**	@name	modelToWorld
	@text	Transform a point in model space to world space.
	
	@in		MOAITransform self
	@in		x
	@in		y
	@out	x
	@out	y
*/
int MOAITransform::_modelToWorld ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )

	USVec2D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );

	USAffine2D modelToWorld = self->GetLocalToWorldMtx ();
	modelToWorld.Transform ( loc );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );

	return 2;
}

//----------------------------------------------------------------//
/**	@name	move
	@text	Animate the transform by applying a delta. Creates and returns
			a MOAIEaseDriver initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number xDelta		Delta to be added to x.
	@in		number yDelta		Delta to be added to y.
	@in		number rDelta		Delta to be added to r (in degrees).
	@in		number xSclDelta	Delta to be added to x scale.
	@in		number ySclDelta	Delta to be added to y scale.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_move ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNNNNNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 5 );
	
	float xLoc		= state.GetValue < float >( 2, 0.0f );
	float yLoc		= state.GetValue < float >( 3, 0.0f );
	float zRot		= state.GetValue < float >( 4, 0.0f );
	float xScl		= state.GetValue < float >( 5, 0.0f );
	float yScl		= state.GetValue < float >( 6, 0.0f );
	float delay		= state.GetValue < float >( 7, 0.0f );
	u32 mode		= state.GetValue < u32 >( 8, USInterpolate::kSmooth );
	
	action->SetLink ( 0, self, MOAITransform::ATTR_X_LOC, xLoc, mode );
	action->SetLink ( 1, self, MOAITransform::ATTR_Y_LOC, yLoc, mode );
	action->SetLink ( 2, self, MOAITransform::ATTR_Z_ROT, zRot, mode );
	action->SetLink ( 3, self, MOAITransform::ATTR_X_SCL, xScl, mode );
	action->SetLink ( 4, self, MOAITransform::ATTR_Y_SCL, yScl, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	moveLoc
	@text	Animate the transform by applying a delta. Creates and returns
			a MOAIEaseDriver initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number xDelta		Delta to be added to x.
	@in		number yDelta		Delta to be added to y.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_moveLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 2 );
	
	float xLoc		= state.GetValue < float >( 2, 0.0f );
	float yLoc		= state.GetValue < float >( 3, 0.0f );
	float delay		= state.GetValue < float >( 4, 0.0f );
	u32 mode		= state.GetValue < u32 >( 5, USInterpolate::kSmooth );
	
	action->SetLink ( 0, self, MOAITransform::ATTR_X_LOC, xLoc, mode );
	action->SetLink ( 1, self, MOAITransform::ATTR_Y_LOC, yLoc, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	moveRot
	@text	Animate the transform by applying a delta. Creates and returns
			a MOAIEaseDriver initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number rDelta		Delta to be added to r (in degrees).
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_moveRot ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 1 );
	
	float zRot		= state.GetValue < float >( 2, 0.0f );
	float delay		= state.GetValue < float >( 3, 0.0f );
	u32 mode		= state.GetValue < u32 >( 4, USInterpolate::kSmooth );
	
	action->SetLink ( 0, self, MOAITransform::ATTR_Z_ROT, zRot, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	moveScl
	@text	Animate the transform by applying a delta. Creates and returns
			a MOAIEaseDriver initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number xSclDelta	Delta to be added to x scale.
	@in		number ySclDelta	Delta to be added to y scale.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_moveScl ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 2 );
	
	float xScl		= state.GetValue < float >( 2, 0.0f );
	float yScl		= state.GetValue < float >( 3, 0.0f );
	float delay		= state.GetValue < float >( 4, 0.0f );
	u32 mode		= state.GetValue < u32 >( 5, USInterpolate::kSmooth );
	
	action->SetLink ( 0, self, MOAITransform::ATTR_X_SCL, xScl, mode );
	action->SetLink ( 1, self, MOAITransform::ATTR_Y_SCL, yScl, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	seek
	@text	Animate the transform by applying a delta. Delta is computed
			given a target value. Creates and returns a MOAIEaseDriver
			initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number xGoal		Desired resulting value for x.
	@in		number yGoal		Desired resulting value for y.
	@in		number rGoal		Desired resulting value for r (in degrees).
	@in		number xSclGoal		Desired resulting value for x scale.
	@in		number ySclGoal		Desired resulting value for y scale.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_seek ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNNNNNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 5 );
	
	float xLoc		= state.GetValue < float >( 2, 0.0f );
	float yLoc		= state.GetValue < float >( 3, 0.0f );
	float zRot		= state.GetValue < float >( 4, 0.0f );
	float xScl		= state.GetValue < float >( 5, 0.0f );
	float yScl		= state.GetValue < float >( 6, 0.0f );
	float delay		= state.GetValue < float >( 7, 0.0f );
	u32 mode		= state.GetValue < u32 >( 8, USInterpolate::kSmooth );

	action->SetLink ( 0, self, MOAITransform::ATTR_X_LOC, xLoc - self->mLoc.mX, mode );
	action->SetLink ( 1, self, MOAITransform::ATTR_Y_LOC, yLoc - self->mLoc.mY, mode );
	action->SetLink ( 2, self, MOAITransform::ATTR_Z_ROT, zRot - self->mDegrees, mode );
	action->SetLink ( 3, self, MOAITransform::ATTR_X_SCL, xScl - self->mScale.mX, mode );
	action->SetLink ( 4, self, MOAITransform::ATTR_Y_SCL, yScl - self->mScale.mY, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	seekLoc
	@text	Animate the transform by applying a delta. Delta is computed
			given a target value. Creates and returns a MOAIEaseDriver
			initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number xGoal		Desired resulting value for x.
	@in		number yGoal		Desired resulting value for y.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_seekLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 2 );
	
	float xLoc		= state.GetValue < float >( 2, 0.0f );
	float yLoc		= state.GetValue < float >( 3, 0.0f );
	float delay		= state.GetValue < float >( 4, 0.0f );
	u32 mode		= state.GetValue < u32 >( 5, USInterpolate::kSmooth );

	action->SetLink ( 0, self, MOAITransform::ATTR_X_LOC, xLoc - self->mLoc.mX, mode );
	action->SetLink ( 1, self, MOAITransform::ATTR_Y_LOC, yLoc - self->mLoc.mY, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	seekRot
	@text	Animate the transform by applying a delta. Delta is computed
			given a target value. Creates and returns a MOAIEaseDriver
			initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number rGoal		Desired resulting value for r (in degrees).
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_seekRot ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 1 );
	
	float zRot		= state.GetValue < float >( 2, 0.0f );
	float delay		= state.GetValue < float >( 3, 0.0f );
	u32 mode		= state.GetValue < u32 >( 4, USInterpolate::kSmooth );

	action->SetLink ( 0, self, MOAITransform::ATTR_Z_ROT, zRot - self->mDegrees, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	seekScl
	@text	Animate the transform by applying a delta. Delta is computed
			given a target value. Creates and returns a MOAIEaseDriver
			initialized to apply the delta.
	
	@in		MOAITransform self
	@in		number xSclGoal		Desired resulting value for x scale.
	@in		number ySclGoal		Desired resulting value for y scale.
	@in		number length		Length of animation in seconds.
	@opt	number mode			The ease mode. One of MOAIEaseType.EASE_IN, MOAIEaseType.EASE_OUT, MOAIEaseType.FLAT MOAIEaseType.LINEAR,
								MOAIEaseType.SMOOTH, MOAIEaseType.SOFT_EASE_IN, MOAIEaseType.SOFT_EASE_OUT, MOAIEaseType.SOFT_SMOOTH

	@out	MOAIEaseDriver easeDriver
*/
int MOAITransform::_seekScl ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNNN" )

	MOAIEaseDriver* action = new MOAIEaseDriver ();
	action->ReserveLinks ( 2 );
	
	float xScl		= state.GetValue < float >( 2, 0.0f );
	float yScl		= state.GetValue < float >( 3, 0.0f );
	float delay		= state.GetValue < float >( 4, 0.0f );
	u32 mode		= state.GetValue < u32 >( 5, USInterpolate::kSmooth );

	action->SetLink ( 0, self, MOAITransform::ATTR_X_SCL, xScl - self->mScale.mX, mode );
	action->SetLink ( 1, self, MOAITransform::ATTR_Y_SCL, yScl - self->mScale.mY, mode );
	
	action->SetLength ( delay );
	action->Start ();
	action->PushLuaUserdata ( state );

	return 1;
}

//----------------------------------------------------------------//
/**	@name	setLoc
	@text	Sets the transform's location.
	
	@in		MOAITransform self
	@in		number x
	@in		number y
	@out	nil
*/
int MOAITransform::_setLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )
	
	USVec2D loc;
	
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );
	
	self->SetLoc ( loc );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setParent
	@text	Sets or clears the prop's parent transform.
	
	@in		MOAIProp2D self
	@opt	MOAIProp2D parent	Default value is nil.
	@out	nil
*/
int MOAITransform::_setParent ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "U" )
	
	MOAITransformBase* parent = state.GetLuaObject < MOAITransformBase >( 2 );
	self->SetParent ( parent );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setRot
	@text	Sets the transform's rotation.
	
	@in		MOAITransform self
	@in		number rot			Rotation in degrees.
	@out	nil
*/
int MOAITransform::_setRot ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UN" )
	
	float d = state.GetValue < float >( 2, 0.0f );
	
	self->SetRot ( d );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setScl
	@text	Sets the transform's scale.
	
	@in		MOAITransform self
	@in		number xScl
	@in		number yScl
	@out	nil
*/
int MOAITransform::_setScl ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )
	
	USVec2D scl;
	
	scl.mX = state.GetValue < float >( 2, 0.0f );
	scl.mY = state.GetValue < float >( 3, 0.0f );
	
	self->SetScl ( scl );
	self->ScheduleUpdate ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	worldToModel
	@text	Transform a point in world space to model space.
	
	@in		MOAITransform self
	@in		x
	@in		y
	@out	x
	@out	y
*/
int MOAITransform::_worldToModel ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITransform, "UNN" )

	USVec2D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );

	USAffine2D worldToModel = self->GetWorldToLocalMtx ();
	worldToModel.Transform ( loc );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );

	return 2;
}

//================================================================//
// MOAITransform
//================================================================//

//----------------------------------------------------------------//
void MOAITransform::ApplyAttrOp ( u32 attrID, USAttrOp& attrOp ) {

	switch ( attrID ) {
		case ATTR_X_LOC:
			this->mLoc.mX = attrOp.Op ( this->mLoc.mX );
			return;
		case ATTR_Y_LOC:
			this->mLoc.mY = attrOp.Op ( this->mLoc.mY );
			return;
		case ATTR_Z_ROT:
			this->mDegrees = attrOp.Op ( this->mDegrees );
			return;
		case ATTR_X_SCL:
			this->mScale.mX = attrOp.Op ( this->mScale.mX );
			return;
		case ATTR_Y_SCL:
			this->mScale.mY = attrOp.Op ( this->mScale.mY );
			return;
	}
}

//----------------------------------------------------------------//
void MOAITransform::BuildTransforms ( float xOff, float yOff, float xStretch, float yStretch ) {
	
	this->mLocalToWorldMtx.ScRoTr (
		this->mScale.mX * xStretch,
		this->mScale.mY * yStretch,
		( float )D2R * this->mDegrees,
		this->mLoc.mX + xOff,
		this->mLoc.mY + yOff
	);
	
	if ( this->mParent ) {
	
		USAffine2D inherit;
		inherit.Ident ();
		
		if ( this->mParent ) {
			inherit.Append ( this->mParent->GetLocalToWorldMtx ());
		}
		
		if ( this->mFilter == INHERIT_ALL ) {
			this->mLocalToWorldMtx.Append ( inherit );
		}
		
		else if ( this->mFilter == INHERIT_LOC ) {
			
			USVec2D loc ( 0.0f, 0.0f );
			inherit.Transform ( loc );
			
			USAffine2D mtx;
			mtx.Translate ( loc );
			
			this->mLocalToWorldMtx.Append ( mtx );
		}
	}
	
	this->mWorldToLocalMtx.Inverse ( this->mLocalToWorldMtx );
}

//----------------------------------------------------------------//
const USAffine2D& MOAITransform::GetLocalToWorldMtx () {

	return this->mLocalToWorldMtx;
}

//----------------------------------------------------------------//
const USAffine2D& MOAITransform::GetWorldToLocalMtx () {

	return this->mWorldToLocalMtx;
}

//----------------------------------------------------------------//
MOAITransform::MOAITransform () :
	mLoc ( 0.0f, 0.0f ),
	mScale ( 1.0f, 1.0f ),
	mDegrees ( 0.0f ),
	mFilter ( INHERIT_ALL ) {
	
	RTTI_SINGLE ( MOAITransformBase )
	
	this->mLocalToWorldMtx.Ident ();
	this->mWorldToLocalMtx.Ident ();
}

//----------------------------------------------------------------//
MOAITransform::~MOAITransform () {

	this->mParent = 0;
}

//----------------------------------------------------------------//
void MOAITransform::OnDepNodeUpdate () {
	
	this->BuildTransforms ( 0.0f, 0.0f, 1.0f, 1.0f );
}

//----------------------------------------------------------------//
void MOAITransform::RegisterLuaClass ( USLuaState& state ) {
	
	MOAINode::RegisterLuaClass ( state );
	
	state.SetField ( -1, "ATTR_X_LOC", ( u32 )ATTR_X_LOC );
	state.SetField ( -1, "ATTR_Y_LOC", ( u32 )ATTR_Y_LOC );
	state.SetField ( -1, "ATTR_Z_ROT", ( u32 )ATTR_Z_ROT );
	state.SetField ( -1, "ATTR_X_SCL", ( u32 )ATTR_X_SCL );
	state.SetField ( -1, "ATTR_Y_SCL", ( u32 )ATTR_Y_SCL );
}

//----------------------------------------------------------------//
void MOAITransform::RegisterLuaFuncs ( USLuaState& state ) {
	
	MOAINode::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "addLoc",				_addLoc },
		{ "addRot",				_addRot },
		{ "addScl",				_addScl },
		{ "getLoc",				_getLoc },
		{ "getRot",				_getRot },
		{ "getScl",				_getScl },
		{ "modelToWorld",		_modelToWorld },
		{ "move",				_move },
		{ "moveLoc",			_moveLoc },
		{ "moveRot",			_moveRot },
		{ "moveScl",			_moveScl },
		{ "seek",				_seek },
		{ "seekLoc",			_seekLoc },
		{ "seekRot",			_seekRot },
		{ "seekScl",			_seekScl },
		{ "setLoc",				_setLoc },
		{ "setParent",			_setParent },
		{ "setRot",				_setRot },
		{ "setScl",				_setScl },
		{ "worldToModel",		_worldToModel },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITransform::SetLoc ( float x, float y ) {

	this->mLoc.mX = x;
	this->mLoc.mY = y;
}

//----------------------------------------------------------------//
void MOAITransform::SetParent ( MOAITransformBase* parent ) {

	if ( this->mParent == parent ) return;
	
	if ( this->mParent ) {
		this->ClearDependency ( *this->mParent );
	}

	this->mParent = parent;
	
	if ( parent ) {
		this->SetDependency ( *parent );
	}

	this->ScheduleUpdate ();
}

//----------------------------------------------------------------//
void MOAITransform::SetScl ( float x, float y ) {

	this->mScale.mX = x;
	this->mScale.mY = y;
}

//----------------------------------------------------------------//
STLString MOAITransform::ToString () {

	STLString repr;

	PRETTY_PRINT ( repr, mLoc )
	PRETTY_PRINT ( repr, mScale )
	PRETTY_PRINT ( repr, mDegrees )

	return repr;
}
