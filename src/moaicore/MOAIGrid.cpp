// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIGrid.h>
#include <moaicore/MOAILogMessages.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	clearTileFlags
	@text	Clears bits specified in mask.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@in		number mask
	@out	nil
*/
int MOAIGrid::_clearTileFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	u32 mask	= state.GetValue < u32 >( 4, 0 );
	
	u32 tile = self->GetTile ( xTile, yTile );
	
	tile = tile & ~mask;
	
	self->SetTile ( xTile, yTile, tile );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getSize
	@text	Returns the dimensions of the grid (in tiles).

	@in		MOAIGrid self
	@out	number width
	@out	number height
*/
int MOAIGrid::_getSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "U" )

	state.Push ( self->mWidth );
	state.Push ( self->mHeight );
	
	return 2;
}

//----------------------------------------------------------------//
/**	@name	getTile
	@text	Returns the value of a given tile.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@out	number tile
*/
int MOAIGrid::_getTile ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	
	u32 tile = self->GetTile ( xTile, yTile );
	state.Push ( tile );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getTileFlags
	@text	Returns the masked value of a given tile.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@in		number mask
	@out	number tile
*/
int MOAIGrid::_getTileFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	u32 mask	= state.GetValue < u32 >( 4, 0 );
	
	u32 tile = self->GetTile ( xTile, yTile );
	
	tile = tile & mask;
	
	lua_pushnumber ( state, tile );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@name	getTileLoc
	@text	Returns the grid space coordinate of the tile. The optional 'position'
			flag determines the location of the coordinate within the tile.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@opt	number position		See MOAIGrid for list of positions. Default it MOAIGrid.TILE_CENTER.
	@out	number x
	@out	number y
*/
int MOAIGrid::_getTileLoc ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNN" )
	
	MOAICellCoord coord;
	
	coord.mX		= state.GetValue < int >( 2, 1 ) - 1;
	coord.mY		= state.GetValue < int >( 3, 1 ) - 1;
	u32 position	= state.GetValue < u32 >( 4, MOAIGridSpace::TILE_CENTER );
	
	USVec2D loc = self->GetTilePoint ( coord, position );
	state.Push ( loc.mX );
	state.Push ( loc.mY );
	return 2;
}

//----------------------------------------------------------------//
/**	@name	locToCoord
	@text	Transforms a coordinate in grid space into a tile index.

	@in		MOAIGrid self
	@in		number x
	@in		number y
	@out	number xTile
	@out	number yTile
*/
int MOAIGrid::_locToCoord ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNN" )

	USVec2D loc;
	loc.mX = state.GetValue < float >( 2, 0 );
	loc.mY = state.GetValue < float >( 3, 0 );
	
	MOAICellCoord coord;
	coord = self->GetCellCoord ( loc );

	state.Push ( coord.mX + 1 );
	state.Push ( coord.mY + 1);
	return 2;
}

//----------------------------------------------------------------//
/**	@name	setRow
	@text	Initializes a grid row given a variable argument list of values.

	@in		MOAIGrid self
	@in		number row
	@in		...
	@out	nil
*/
int MOAIGrid::_setRow ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UN" )

	u32 row = state.GetValue < u32 >( 2, 1 ) - 1;
	u32 total = lua_gettop ( state ) - 2;
	
	for ( u32 i = 0; i < total; ++i ) {
	
		u32 tile = state.GetValue < u32 >( 3 + i, 0 );
		self->SetTile ( i, row, tile );
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSize
	@text	Initializes dimensions of grid and reserves storage for tiles.

	@in		MOAIGrid self
	@in		number width
	@in		number height
	@in		number cellWidth	Default value is 1.
	@in		number cellHeight	Default value is 1.
	@opt	number xOff			X offset of the tile from the cell.
	@opt	number yOff			Y offset of the tile from the cell.
	@opt	number tileWidth	Default value is cellWidth.
	@opt	number tileHeight	Default value is cellHeight.
	@out	nil
*/
int MOAIGrid::_setSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNN" )

	u32 width			= state.GetValue < u32 >( 2, 0 );
	u32 height			= state.GetValue < u32 >( 3, 0 );
	
	float cellWidth		= state.GetValue < float >( 4, 1.0f );
	float cellHeight	= state.GetValue < float >( 5, 1.0f );

	float xOff			= state.GetValue < float >( 6, 0.0f );
	float yOff			= state.GetValue < float >( 7, 0.0f );
	
	float tileWidth		= state.GetValue < float >( 8, cellWidth );
	float tileHeight	= state.GetValue < float >( 9, cellHeight );
	
	self->SetWidth ( width );
	self->SetHeight ( height );
	
	self->SetCellWidth ( cellWidth );
	self->SetCellHeight ( cellHeight );
	
	self->SetXOff ( xOff );
	self->SetYOff ( yOff );
	
	self->SetTileWidth ( tileWidth );
	self->SetTileHeight ( tileHeight );
	
	self->mTiles.Init ( self->GetTotalCells ());
	self->mTiles.Fill ( 0 );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setTile
	@text	Sets the value of a given tile

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@in		number value
	@out	nil
*/
int MOAIGrid::_setTile ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	u32 tile	= state.GetValue < u32 >( 4, 0 );
	
	self->SetTile ( xTile, yTile, tile );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setTileFlags
	@text	Sets a tile's flags given a mask.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@in		number mask
	@out	nil
*/
int MOAIGrid::_setTileFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	u32 mask	= state.GetValue < u32 >( 4, 0 );
	
	u32 tile = self->GetTile ( xTile, yTile );
	
	tile = tile | mask;
	
	self->SetTile ( xTile, yTile, tile );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	toggleTileFlags
	@text	Toggles a tile's flags given a mask.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@in		number mask
	@out	nil
*/
int MOAIGrid::_toggleTileFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNNN" )

	int xTile	= state.GetValue < int >( 2, 1 ) - 1;
	int yTile	= state.GetValue < int >( 3, 1 ) - 1;
	u32 mask	= state.GetValue < u32 >( 4, 0 );
	
	u32 tile = self->GetTile ( xTile, yTile );
	
	tile = tile ^ mask;
	
	self->SetTile ( xTile, yTile, tile );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	wrapCoord
	@text	Wraps a tile index to the range of the grid.

	@in		MOAIGrid self
	@in		number xTile
	@in		number yTile
	@out	number xTile
	@out	number yTile
*/
int MOAIGrid::_wrapCoord ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGrid, "UNN" )
	
	MOAICellCoord coord;
	coord.mX = state.GetValue < int >( 2, 1 ) - 1;
	coord.mY = state.GetValue < int >( 3, 1 ) - 1;

	self->WrapCellCoord ( coord );
	
	state.Push ( coord.mX + 1 );
	state.Push ( coord.mY + 1 );
	return 2;
}

//================================================================//
// MOAIGrid
//================================================================//

//----------------------------------------------------------------//
u32 MOAIGrid::GetTile ( int xTile, int yTile ) {

	MOAICellCoord coord ( xTile, yTile );
	u32 addr = this->GetCellAddr ( coord );
	if ( addr < this->mTiles.Size ()) {
		return this->mTiles [ addr ];
	}
	return 0;
}

//----------------------------------------------------------------//
MOAIGrid::MOAIGrid () {
	
	RTTI_BEGIN
		RTTI_EXTEND ( USLuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIGrid::~MOAIGrid () {
}

//----------------------------------------------------------------//
void MOAIGrid::RegisterLuaClass ( USLuaState& state ) {

	state.SetField ( -1, "TILE_X_FLIP", ( u32 )MOAITileFlags::XFLIP );
	state.SetField ( -1, "TILE_Y_FLIP", ( u32 )MOAITileFlags::YFLIP );
	state.SetField ( -1, "TILE_XY_FLIP", ( u32 )MOAITileFlags::FLIP_MASK );
	state.SetField ( -1, "TILE_HIDE", ( u32 )MOAITileFlags::HIDDEN );
	
	state.SetField ( -1, "TILE_LEFT_TOP", ( u32 )MOAIGridSpace::TILE_LEFT_TOP );
	state.SetField ( -1, "TILE_RIGHT_TOP", ( u32 )MOAIGridSpace::TILE_RIGHT_TOP );
	state.SetField ( -1, "TILE_LEFT_BOTTOM", ( u32 )MOAIGridSpace::TILE_LEFT_BOTTOM );
	state.SetField ( -1, "TILE_RIGHT_BOTTOM", ( u32 )MOAIGridSpace::TILE_RIGHT_BOTTOM );
	
	state.SetField ( -1, "TILE_LEFT_CENTER", ( u32 )MOAIGridSpace::TILE_LEFT_CENTER );
	state.SetField ( -1, "TILE_RIGHT_CENTER", ( u32 )MOAIGridSpace::TILE_RIGHT_CENTER );
	state.SetField ( -1, "TILE_TOP_CENTER", ( u32 )MOAIGridSpace::TILE_TOP_CENTER );
	state.SetField ( -1, "TILE_BOTTOM_CENTER", ( u32 )MOAIGridSpace::TILE_BOTTOM_CENTER );
	
	state.SetField ( -1, "TILE_CENTER", ( u32 )MOAIGridSpace::TILE_CENTER );
}

//----------------------------------------------------------------//
void MOAIGrid::RegisterLuaFuncs ( USLuaState& state ) {

	luaL_Reg regTable [] = {
		{ "clearTileFlags",		_clearTileFlags },
		{ "getSize",			_getSize },
		{ "getTile",			_getTile },
		{ "getTileFlags",		_getTileFlags },
		{ "getTileLoc",			_getTileLoc },
		{ "locToCoord",			_locToCoord },
		{ "setRow",				_setRow },
		{ "setSize",			_setSize },
		{ "setTile",			_setTile },
		{ "setTileFlags",		_setTileFlags },
		{ "toggleTileFlags",	_toggleTileFlags },
		{ "wrapCoord",			_wrapCoord },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGrid::SerializeIn ( USLuaState& state, USLuaSerializer& serializer ) {
	UNUSED ( serializer );

	this->MOAIGridSpace::SerializeIn ( state );
	this->mTiles.Init ( this->MOAIGridSpace::GetTotalCells ());

	state.GetField ( -1, "mData" );

	if ( state.IsType ( -1, LUA_TSTRING )) {
		
		void* tiles = this->mTiles;
		size_t tilesSize = this->mTiles.Size () * sizeof ( u32 );
		
		STLString base64 = lua_tostring ( state, -1 ); 
		base64.base_64_decode ( tiles, tilesSize );
		
		USLeanArray < u8 > unzip;
		USZip::Inflate ( this->mTiles, this->mTiles.Size () * sizeof ( u32 ), unzip );
		
		tiles = unzip.Data ();
		if ( unzip.Size () < tilesSize ) {
			tilesSize = unzip.Size ();
		}
		memcpy ( this->mTiles, tiles, tilesSize );
	}
	
	lua_pop ( state, 1 );
}

//----------------------------------------------------------------//
void MOAIGrid::SerializeOut ( USLuaState& state, USLuaSerializer& serializer ) {
	UNUSED ( serializer );

	this->MOAIGridSpace::SerializeOut ( state );

	USLeanArray < u8 > zip;
	USZip::Deflate ( this->mTiles, this->mTiles.Size () * sizeof ( u32 ), zip );

	STLString base64;
	base64.base_64_encode ( zip.Data (), zip.Size ());
	
	lua_pushstring ( state, base64.str ());
	lua_setfield ( state, -2, "mData" );
}

//----------------------------------------------------------------//
void MOAIGrid::SetTile ( u32 addr, u32 tile ) {

	u32 size = this->mTiles.Size ();

	if ( size ) {
		addr = addr % this->mTiles.Size ();
		this->mTiles [ addr ] = tile;
	}
}

//----------------------------------------------------------------//
void MOAIGrid::SetTile ( int xTile, int yTile, u32 tile ) {

	u32 size = this->mTiles.Size ();
	
	if ( size ) {

		MOAICellCoord coord ( xTile, yTile );
		u32 addr = this->GetCellAddr ( coord );
		if ( addr < this->mTiles.Size ()) {
			this->mTiles [ addr ] = tile;
		}
	}
}

//----------------------------------------------------------------//
u32 MOAIGrid::Size () {

	return this->mTiles.Size ();
}
