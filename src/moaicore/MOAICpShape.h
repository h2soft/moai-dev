// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAICPSHAPE_H
#define	MOAICPSHAPE_H
#if USE_CHIPMUNK

#include <moaicore/MOAICpSpace.h>

struct cpShape;

//================================================================//
// MOAICpShape
//================================================================//
/**	@brief Chipmunk Shape.
*/
class MOAICpShape :
	public virtual USLuaObject,
	public MOAICpPrim {
private:

	enum {
		MAX_POLY_VERTS = 1024,
	};

	USLeanLink < MOAICpShape* > mLinkInBody;
	cpShape* mShape;

	//----------------------------------------------------------------//
	static int	_areaForCircle		( lua_State* L );
	static int	_areaForPolygon		( lua_State* L );
	static int	_areaForRect		( lua_State* L );
	static int	_areaForSegment		( lua_State* L );
	static int	_getBody			( lua_State* L );
	static int	_getElasticity		( lua_State* L );
	static int	_getFriction		( lua_State* L );
	static int	_getGroup			( lua_State* L );
	static int	_getLayers			( lua_State* L );
	static int	_getSurfaceVel		( lua_State* L );
	static int	_getType			( lua_State* L );
	static int	_inside				( lua_State* L );
	static int	_isSensor			( lua_State* L );
	static int	_momentForCircle	( lua_State* L );
	static int	_momentForPolygon	( lua_State* L );
	static int	_momentForRect		( lua_State* L );
	static int	_momentForSegment	( lua_State* L );
	static int	_new				( lua_State* L );
	static int	_setElasticity		( lua_State* L );
	static int	_setFriction		( lua_State* L );
	static int	_setGroup			( lua_State* L );
	static int	_setIsSensor		( lua_State* L );
	static int	_setLayers			( lua_State* L );
	static int	_setSurfaceVel		( lua_State* L );
	static int	_setType			( lua_State* L );
	
	//----------------------------------------------------------------//
	void			CpAddToSpace			( cpSpace* space );
	void			CpRemoveFromSpace		( cpSpace* space );
	static u32		LoadVerts				( USLuaState& state, int idx, void* buffer, u32 max  );

public:
	
	friend class MOAICpBody;
	friend class MOAICpSpace;
	
	DECL_LUA_FACTORY ( MOAICpShape )
	
	//----------------------------------------------------------------//
					MOAICpShape				();
					~MOAICpShape			();
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );
	STLString		ToString				();
};

#endif
#endif