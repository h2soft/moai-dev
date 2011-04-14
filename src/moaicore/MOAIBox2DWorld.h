// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIBOX2DWORLD_H
#define	MOAIBOX2DWORLD_H
#if USE_BOX2D

#include <Box2D/Box2D.h>
#include <moaicore/MOAIAction.h>

class b2World;
class MOAIBox2DArbiter;
class MOAIBox2DDebugDraw;
class MOAIBox2DWorld;

//================================================================//
// MOAIBox2DPrim
//================================================================//
class MOAIBox2DPrim :
	public virtual USLuaObject  {
protected:

	MOAIBox2DWorld* mWorld;

	//----------------------------------------------------------------//
	
public:

	friend class MOAIBox2DWorld;

	GET_SET ( MOAIBox2DWorld*, World, mWorld )

	//----------------------------------------------------------------//
	float			GetUnitsToMeters		();
					MOAIBox2DPrim			();
};

//================================================================//
// MOAIBox2DWorld
//================================================================//
/**	@name	MOAIBox2DWorld
	@text	Box2D world.
*/
class MOAIBox2DWorld :
	public MOAIAction,
	public b2DestructionListener {
private:

	b2World*					mWorld;
	MOAIBox2DDebugDraw*			mDebugDraw;
	
	USRef < MOAIBox2DArbiter >	mArbiter;

	u32		mVelocityIterations;
	u32		mPositionIterations;
	
	float	mUnitsToMeters; // maps world space units to meters

	//----------------------------------------------------------------//
	static int	_addBody						( lua_State* L );
	static int	_addDistanceJoint				( lua_State* L );
	static int	_addFrictionJoint				( lua_State* L );
	static int	_addGearJoint					( lua_State* L );
	static int	_addLineJoint					( lua_State* L );
	static int	_addMouseJoint					( lua_State* L );
	static int	_addPrismaticJoint				( lua_State* L );
	static int	_addPulleyJoint					( lua_State* L );
	static int	_addRevoluteJoint				( lua_State* L );
	static int	_addWeldJoint					( lua_State* L );
	static int	_destroyBody					( lua_State* L );
	static int	_destroyJoint					( lua_State* L );
	static int	_getAutoClearForces				( lua_State* L );
	static int	_getGravity						( lua_State* L );
	static int	_setAutoClearForces				( lua_State* L );
	static int	_setGravity						( lua_State* L );
	static int	_setIterations					( lua_State* L );
	static int	_setUnitsToMeters				( lua_State* L );
	
	//----------------------------------------------------------------//
	void		SayGoodbye		( b2Fixture* fixture ); 
	void		SayGoodbye		( b2Joint* joint ); 

public:
	
	DECL_LUA_FACTORY ( MOAIBox2DWorld )
	
	GET_SET ( float, UnitsToMeters, mUnitsToMeters )
	
	//----------------------------------------------------------------//
	void			DrawDebug				();
	bool			IsDone					();
					MOAIBox2DWorld			();
					~MOAIBox2DWorld			();
	void			OnUpdate				( float step );
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );
	STLString		ToString				();
};

#endif
#endif