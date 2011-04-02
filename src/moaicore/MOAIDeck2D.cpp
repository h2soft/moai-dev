// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIDeck2D.h>
#include <moaicore/MOAIGrid.h>
#include <moaicore/MOAISurfaceSampler2D.h>
#include <moaicore/MOAITransform.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//

//================================================================//
// MOAIDeck2D
//================================================================//

//----------------------------------------------------------------//
void MOAIDeck2D::Draw ( const USAffine2D& transform, u32 idx ) {
	
	if ( idx & USTile::HIDDEN ) return;
	
	USDrawBuffer& drawbuffer = USDrawBuffer::Get ();
	drawbuffer.SetVtxTransform ( transform );
	
	float xScale = ( idx & USTile::XFLIP ) ? -1.0f : 1.0f;
	float yScale = ( idx & USTile::YFLIP ) ? -1.0f : 1.0f;
	
	this->Draw ( idx & USTile::CODE_MASK, 0.0f, 0.0, xScale, yScale );
}

//----------------------------------------------------------------//
void MOAIDeck2D::Draw ( u32 idx, float xOff, float yOff, float xScale, float yScale ) {
	UNUSED ( idx );
	UNUSED ( xOff );
	UNUSED ( yOff );
	UNUSED ( xScale );
	UNUSED ( yScale );
}

//----------------------------------------------------------------//
void MOAIDeck2D::Draw ( const USAffine2D& transform, MOAIGrid& grid, USTileCoord& c0, USTileCoord& c1 ) {
	
	USDrawBuffer& drawbuffer = USDrawBuffer::Get ();
	drawbuffer.SetVtxTransform ( transform );

	float width = grid.GetTileWidth ();
	float height = grid.GetTileHeight ();

	for ( int y = c0.mY; y <= c1.mY; ++y ) {
		for ( int x = c0.mX; x <= c1.mX; ++x ) {
			
			u32 idx = grid.GetTile ( x, y );
			if ( idx & USTile::HIDDEN ) continue;
			
			USVec2D loc = grid.GetTilePoint ( x, y, USGridSpace::TILE_CENTER );
			
			float xScale = ( idx & USTile::XFLIP ) ? -width : width;
			float yScale = ( idx & USTile::YFLIP ) ? -height : height;
			
			this->Draw ( idx & USTile::CODE_MASK, loc.mX, loc.mY, xScale, yScale );
		}
	}
}

//----------------------------------------------------------------//
void MOAIDeck2D::DrawDebug ( const USAffine2D& transform, u32 idx ) {
	UNUSED ( transform );
	UNUSED ( idx );
}

//----------------------------------------------------------------//
void MOAIDeck2D::DrawDebug ( const USAffine2D& transform, MOAIGrid& grid, USTileCoord& c0, USTileCoord& c1 ) {
	UNUSED ( transform );
	UNUSED ( grid );
	UNUSED ( c0 );
	UNUSED ( c1 );
}

//----------------------------------------------------------------//
void MOAIDeck2D::GatherSurfaces ( u32 idx, MOAISurfaceSampler2D& sampler ) {
	UNUSED ( idx );
	UNUSED ( sampler );
}

//----------------------------------------------------------------//
void MOAIDeck2D::GatherSurfaces ( MOAIGrid& grid, USTileCoord& c0, USTileCoord& c1, MOAISurfaceSampler2D& sampler ) {
	UNUSED ( grid );
	UNUSED ( c0 );
	UNUSED ( c1 );
	UNUSED ( sampler );
}

//----------------------------------------------------------------//
MOAIDeck2D::MOAIDeck2D () {
	
	RTTI_SINGLE ( MOAIDeck )
}

//----------------------------------------------------------------//
MOAIDeck2D::~MOAIDeck2D () {
}

//----------------------------------------------------------------//
void MOAIDeck2D::RegisterLuaClass ( USLuaState& state ) {

	this->MOAIDeck::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAIDeck2D::RegisterLuaFuncs ( USLuaState& state ) {

	this->MOAIDeck::RegisterLuaFuncs ( state );
}