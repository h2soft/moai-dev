// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <Box2D/Box2D.h>
#include <moaicore/MOAIBox2DArbiter.h>
#include <moaicore/MOAIBox2DFixture.h>
#include <moaicore/MOAIBox2DWorld.h>

SUPPRESS_EMPTY_FILE_WARNING
#if USE_BOX2D

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	setCollisionHandler
	@text	Sets a Lua function to call when collisions occur.
	
	@in		MOAIBox2DFixture self
	@in		function handler
	@opt	number mask			Bitwise combination of MOAIBox2DArbiter.BEGIN, MOAIBox2DArbiter.END,
								MOAIBox2DArbiter.POST_SOLVE, MOAIBox2DArbiter.PRE_SOLVE,
								MOAIBox2DArbiter.ALL
	@out	nil
*/
int MOAIBox2DFixture::_setCollisionHandler ( lua_State* L ) {
	LUA_SETUP ( MOAIBox2DFixture, "UF" )
	
	self->mCollisionHandler.SetRef ( state, 2, false );
	self->mCollisionMask = state.GetValue < u32 >( 3, MOAIBox2DArbiter::ALL );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setDensity
	@text	See Box2D documentation.
	
	@in		MOAIBox2DFixture self
	@in		number density
	@out	nil
*/
int MOAIBox2DFixture::_setDensity ( lua_State* L ) {
	LUA_SETUP ( MOAIBox2DFixture, "UN" )
	
	float density = state.GetValue < float >( 2, 0.0f );
	self->mFixture->SetDensity ( density );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFilter
	@text	See Box2D documentation.
	
	@in		MOAIBox2DFixture self
	@in		number categoryBits
	@in		number maskBits
	@opt	number groupIndex
	@out	nil
*/
int MOAIBox2DFixture::_setFilter ( lua_State* L ) {
	LUA_SETUP ( MOAIBox2DFixture, "UNN" )
	
	b2Filter filter = self->mFixture->GetFilterData ();
	
	filter.categoryBits		= ( uint16 )state.GetValue < u32 >( 2, 0 );
	filter.maskBits			= ( uint16 )state.GetValue < u32 >( 3, 0 );
	filter.groupIndex		= ( uint16 )state.GetValue < u32 >( 4, ( u32 )filter.groupIndex );
	
	self->mFixture->SetFilterData ( filter );
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFriction
	@text	See Box2D documentation.
	
	@in		MOAIBox2DFixture self
	@in		number friction
	@out	nil
*/
int MOAIBox2DFixture::_setFriction ( lua_State* L ) {
	LUA_SETUP ( MOAIBox2DFixture, "UN" )
	
	float friction = state.GetValue < float >( 2, 0.0f );
	self->mFixture->SetFriction ( friction );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setRestitution
	@text	See Box2D documentation.
	
	@in		MOAIBox2DFixture self
	@in		number restitution
	@out	nil
*/
int MOAIBox2DFixture::_setRestitution ( lua_State* L ) {
	LUA_SETUP ( MOAIBox2DFixture, "UN" )
	
	float restitution = state.GetValue < float >( 2, 0.0f );
	self->mFixture->SetRestitution ( restitution );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSensor
	@text	See Box2D documentation.
	
	@in		MOAIBox2DFixture self
	@opt	boolean isSensor		Default value is 'true'
	@out	nil
*/
int MOAIBox2DFixture::_setSensor ( lua_State* L ) {
	LUA_SETUP ( MOAIBox2DFixture, "U" )
	
	bool isSensor = state.GetValue < bool >( 2, true );
	self->mFixture->SetSensor ( isSensor );

	return 0;
}

//================================================================//
// MOAIBox2DFixture
//================================================================//

//----------------------------------------------------------------//
void MOAIBox2DFixture::BeginContact ( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter ) {
	
	if ( this->mCollisionMask & MOAIBox2DArbiter::BEGIN ) {
		this->HandleCollision ( MOAIBox2DArbiter::BEGIN, other, arbiter );
	}
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::EndContact ( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter ) {
	
	if ( this->mCollisionMask & MOAIBox2DArbiter::END ) {
		this->HandleCollision ( MOAIBox2DArbiter::END, other, arbiter );
	}
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::HandleCollision ( u32 eventType, MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter ) {
	UNUSED ( other );
	UNUSED ( arbiter );
	
	if ( this->mCollisionHandler ) {
	
		USLuaStateHandle state = USLuaRuntime::Get ().State ();
		if ( this->mCollisionHandler.PushRef ( state )) {
			
			state.Push ( eventType );
			this->PushLuaUserdata ( state );
			other->PushLuaUserdata ( state );
			arbiter->PushLuaUserdata ( state );
			
			state.DebugCall ( 4, 0 );
		}
	}
}

//----------------------------------------------------------------//
u32 MOAIBox2DFixture::LoadVerts ( USLuaState& state, int idx, b2Vec2* verts, u32 max  ) {
	
	int itr = state.PushTableItr ( idx );
	idx = 0;
	
	u32 total = 0;
	for ( ; state.TableItrNext ( itr ) && ( total < max ); ++idx ) {
		
		float val = state.GetValue < float >( -1, 0 );
		
		if ( idx & 0x01 ) {
			verts [ total ].y = val;
			total++;
		}
		else {
			verts [ total ].x = val;
		}
	}
	return total;
}

//----------------------------------------------------------------//
MOAIBox2DFixture::MOAIBox2DFixture () :
	mFixture ( 0 ),
	mCollisionMask ( 0 ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( USLuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIBox2DFixture::~MOAIBox2DFixture () {
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::PostSolve ( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter ) {
	
	if ( this->mCollisionMask & MOAIBox2DArbiter::POST_SOLVE ) {
		this->HandleCollision ( MOAIBox2DArbiter::POST_SOLVE, other, arbiter );
	}
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::PreSolve ( MOAIBox2DFixture* other, MOAIBox2DArbiter* arbiter ) {
	
	if ( this->mCollisionMask & MOAIBox2DArbiter::PRE_SOLVE ) {
		this->HandleCollision ( MOAIBox2DArbiter::PRE_SOLVE, other, arbiter );
	}
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::RegisterLuaClass ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::RegisterLuaFuncs ( USLuaState& state ) {
	
	LuaReg regTable [] = {
		{ "setCollisionHandler",	_setCollisionHandler },
		{ "setDensity",				_setDensity },
		{ "setFilter",				_setFilter },
		{ "setFriction",			_setFriction },
		{ "setRestitution",			_setRestitution },
		{ "setSensor",				_setSensor },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIBox2DFixture::SetFixture ( b2Fixture* fixture ) {

	this->mFixture = fixture;
	if ( fixture ) {
		fixture->SetUserData ( this );
	}
}

//----------------------------------------------------------------//
STLString MOAIBox2DFixture::ToString () {

	STLString repr;
	return repr;
}

#endif
