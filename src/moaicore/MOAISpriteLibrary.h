// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAISPRITELIBRARY_H
#define	MOAISPRITELIBRARY_H

#include <moaicore/MOAIContentLibrary2D.h>

class MOAITexture;

//================================================================//
// USSpriteUVRect
//================================================================//
class USSpriteUVRect {
private:

	friend class MOAISpriteLibrary;

	USRect	mRect;
	u32		mTransform;
};

//================================================================//
// USSpritePrim
//================================================================//
class USSpritePrim {
private:

	friend class MOAISpriteLibrary;

	u32		mUVRectID;
	u32		mQuadID;
};

//================================================================//
// USSprite
//================================================================//
class USSprite {
private:

	friend class MOAISpriteLibrary;

	u32		mBasePrim;
	u32		mTotalPrims;
};

//================================================================//
// MOAISpriteLibrary
//================================================================//
/**	@brief Sprite library class.
*/
class MOAISpriteLibrary :
	public MOAIContentLibrary2D {
private:

	USRef < MOAITexture >			mTexture;
	
	USLeanArray < USSpriteUVRect >	mUVRects;
	USLeanArray < USQuad >			mQuads;
	USLeanArray < USSpritePrim >	mPrims;
	USLeanArray < USSprite >		mSprites;
	
	//----------------------------------------------------------------//
	static int	_bind					( lua_State* L );
	static int	_enumSprites			( lua_State* L );
	static int	_enumUVTiles			( lua_State* L );
	static int	_releaseTexture			( lua_State* L );
	static int	_reservePrims			( lua_State* L );
	static int	_reserveQuads			( lua_State* L );
	static int	_reserveSprites			( lua_State* L );
	static int	_reserveUVRects			( lua_State* L );
	static int	_scaleCoords			( lua_State* L );
	static int	_scaleUVCoords			( lua_State* L );
	static int	_setPrim				( lua_State* L );
	static int	_setQuad				( lua_State* L );
	static int	_setRect				( lua_State* L );
	static int	_setSprite				( lua_State* L );
	static int	_setTexture				( lua_State* L );
	static int	_setUVRect				( lua_State* L );
	static int	_setUVRectTransform		( lua_State* L );
	
	//----------------------------------------------------------------//
	void		Draw					( u32 idx, float xOff, float yOff, float xScale, float yScale );
	
public:
	
	DECL_LUA_DATA ( MOAISpriteLibrary )
	
	enum {
		UV_NONE,
		UV_ROTATE_90,
	};
	
	//----------------------------------------------------------------//
	bool		Bind					();
	bool		Contains				( u32 idx, const USVec2D& vec );
	void		Draw					( MOAIDrawingMtx2D& transform, u32 idx );
	void		Draw					( MOAIDrawingMtx2D& transform, MOAIGrid& grid, USTileCoord& c0, USTileCoord& c1 );
	void		EnumSprites				( u32 idx, u32 basePrimID, u32 uvRectID, u32 screenRectID, u32 total );
	void		EnumUVTiles				( u32 idx, u32 width, u32 height, float xStep, float yStep );
	USRect		GetBounds				( u32 idx );
				MOAISpriteLibrary		();
				~MOAISpriteLibrary		();
	void		RegisterLuaClass		( USLuaState& state );
	void		RegisterLuaFuncs		( USLuaState& state );
	void		ReleaseTexture			();
	void		ReservePrims			( u32 total );
	void		ReserveQuads			( u32 total );
	void		ReserveSprites			( u32 total );
	void		ReserveUVRects			( u32 total );
	void		ScaleScreenCoords		( float xScale, float yScale );
	void		ScaleUVCoords			( float xScale, float yScale );
	void		SetPrim					( u32 idx, u32 uvRectID, u32 screenRectID );
	void		SetQuad					( u32 idx, USQuad& quad );
	void		SetRect					( u32 idx, USRect& rect );
	void		SetSprite				( u32 idx, u32 basePrimID, u32 totalPrims );
	void		SetTexture				( cc8* filename );
	void		SetTexture				( MOAITexture* texture );
	void		SetUVRect				( u32 idx, USRect& rect );
	void		SetUVRectTransform		( u32 idx, u32 transform );
	STLString	ToString				();
};

#endif
