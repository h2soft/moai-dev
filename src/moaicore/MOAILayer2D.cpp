// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIBox2DWorld.h>
#include <moaicore/MOAIDeck.h>
#include <moaicore/MOAICpSpace.h>
#include <moaicore/MOAIDebugLines.h>
#include <moaicore/MOAILayer2D.h>
#include <moaicore/MOAIProp2D.h>
#include <moaicore/MOAITransform.h>

#define MAX_RENDERABLES 512

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@brief <tt>( returns ) getFitting ( self )</tt>\n
\n
	Description of method Coming Soon(tm).
	@param self (in)
	@param y (out)
*/
int MOAILayer2D::_getFitting ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UNNNN" )

	USRect worldRect;
	worldRect.mXMin = state.GetValue < float >( 2, 0.0f );
	worldRect.mYMin = state.GetValue < float >( 3, 0.0f );
	worldRect.mXMax = state.GetValue < float >( 4, 0.0f );
	worldRect.mYMax = state.GetValue < float >( 5, 0.0f );

	worldRect.Bless ();

	float hPad = state.GetValue < float >( 6, 0.0f );
	float vPad = state.GetValue < float >( 7, 0.0f );

	float x = worldRect.mXMin + (( worldRect.mXMax - worldRect.mXMin ) * 0.5f );
	float y = worldRect.mYMin + (( worldRect.mYMax - worldRect.mYMin ) * 0.5f );

	lua_pushnumber ( state, x );
	lua_pushnumber ( state, y );

	float fitting = self->GetFitting ( worldRect, hPad, vPad );
	lua_pushnumber ( state, fitting );

	return 3;
}

//----------------------------------------------------------------//
/**	@brief <tt>( partition ) getPartition ( self )</tt>\n
\n
	Return the partition currently associated with this layer.
	@param self (in)
	@param partition (out)
*/
int	MOAILayer2D::_getPartition ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "U" )

	if ( self->mPartition ) {
		self->mPartition->PushLuaInstance ( state );
		return 1;
	}
	return 0;
}


//----------------------------------------------------------------//
/**	@brief <tt>() insertPrim ( self, prim )</tt>\n
\n
	Inserts a prim into the layer's partition.  This function will automatically
	create a new partition for the layer if none exists.
	A prim should never be inserted into more than one partition.
	@param self (in)
	@param prim (in)
*/
int	MOAILayer2D::_insertPrim ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )

	MOAIProp2D* prop = state.GetLuaData < MOAIProp2D >( 2 );
	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	self->AffirmPartition ();
	self->mPartition->InsertProp ( *prop );

	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>() removePrim ( self, prim )</tt>\n
\n
	Removes a prim from this layer's partition.
	@param self (in)
	@param prim (in)
*/
int	MOAILayer2D::_removePrim ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )

	MOAIProp2D* prop = state.GetLuaData < MOAIProp2D >( 2 );
	if ( !prop ) return 0;
	if ( prop == self ) return 0;

	if ( self->mPartition ) {
		self->mPartition->RemoveProp ( *prop );
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>( returns ) func ( self )</tt>\n
\n
	Description of method Coming Soon(tm).
	@param self (in)
	@param y (out)
*/
int MOAILayer2D::_setBox2DWorld ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )
	
	#if USE_BOX2D
		self->mBox2DWorld = state.GetLuaData < MOAIBox2DWorld >( 2 );
	#endif
	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>() setCamera ( self, camera )</tt>\n
\n
	Sets the layer's camera transform.
	@param self (in)
	@param camera (in) Camera to be set.
*/
int MOAILayer2D::_setCamera ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )

	MOAITransform* camera = state.GetLuaData < MOAITransform >( 2 );
	if ( !camera ) return 0;

	self->SetCamera ( camera );

	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>( returns ) func ( self )</tt>\n
\n
	Description of method Coming Soon(tm).
	@param self (in)
	@param y (out)
*/
int MOAILayer2D::_setCpSpace ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )
	
	#if USE_CHIPMUNK
		self->mCpSpace = state.GetLuaData < MOAICpSpace >( 2 );
	#endif
	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>() setParallax ( self, xScale, yScale )</tt>\n
\n
	Sets the parallax scale for this layer. This is simply a
	scalar applied to the view transform before rendering.
	@param self (in)
	@param xScale (in)
	@param yScale (in)
*/
int MOAILayer2D::_setParallax ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UNN" )

	self->mParallax.mX = state.GetValue < float >( 2, self->mParallax.mX );
	self->mParallax.mY = state.GetValue < float >( 3, self->mParallax.mY );

	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>() setPartition ( self, partition )</tt>\n
\n
	Sets the layer's partition.
	@param self (in)
	@param partition (in)
*/
int MOAILayer2D::_setPartition ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )

	MOAIPartition* partition = state.GetLuaData < MOAIPartition >( 2 );
	if ( !partition ) return 0;

	self->SetPartition ( partition );

	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>() setViewport ( self, viewport )</tt>\n
\n
	Sets the layer's viewport.
	@param self (in)
	@param viewport (in)
*/
int MOAILayer2D::_setViewport ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UU" )

	MOAIViewport* viewport = state.GetLuaData < MOAIViewport >( 2 );
	if ( !viewport ) return 0;

	self->SetViewport ( viewport );

	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>() showDebugLines ( self, show )</tt>\n
\n
	Render debug lines for primitives in this layer.
	(Not all primitives support debug rendering.)
	@param self (in)
	@param show (in)
*/
int	MOAILayer2D::_showDebugLines ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "U" )
	
	self->mShowDebugLines = state.GetValue < bool >( 2, true );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@brief <tt>wndToWorld ( mX, mY )</tt>\n
\n
	Takes a window coordinate and returns (x, y) in world coordinates.
	@param mX Windowed x coordinate to convert.
	@param mY Windowed y coordinate to convert.
*/
int MOAILayer2D::_wndToWorld ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UNN" )

	USVec2D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );

	USAffine2D wndToWorld;
	self->GetWndToWorldMtx ( wndToWorld );
	wndToWorld.Transform ( loc );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );

	return 2;
}

//----------------------------------------------------------------//
/**	@brief <tt>worldToWnd ( mX, mY )</tt>\n
\n
	Takes a world coordinate and returns (x, y) in windowed coordinates.
	@param mX World x coordinate to convert.
	@param mY World y coordinate to convert.
*/
int MOAILayer2D::_worldToWnd ( lua_State* L ) {
	LUA_SETUP ( MOAILayer2D, "UNN" )

	USVec2D loc;
	loc.mX = state.GetValue < float >( 2, 0.0f );
	loc.mY = state.GetValue < float >( 3, 0.0f );

	USAffine2D worldToWnd;
	self->GetWorldToWndMtx ( worldToWnd );
	worldToWnd.Transform ( loc );

	lua_pushnumber ( state, loc.mX );
	lua_pushnumber ( state, loc.mY );

	return 2;
}

//================================================================//
// MOAINode
//================================================================//

//----------------------------------------------------------------//
void MOAILayer2D::AffirmPartition () {

	if ( !this->mPartition ) {
		this->mPartition = new MOAIPartition ();
	}
}

//----------------------------------------------------------------//
void MOAILayer2D::Draw () {

	if ( !this->mViewport ) return;
	
	USViewport viewport = *this->mViewport;
	USDrawBuffer& drawBuffer = USDrawBuffer::Get ();
	
	drawBuffer.Flush ();
	drawBuffer.Reset ();
	
	USAffine2D mtx;
	USCanvas::GetWorldToWndMtx ( mtx, 1.0f, 1.0f );
	mtx.Prepend ( this->mLocalToWorldMtx );
	mtx.Transform ( viewport );
	
	USCamera2D camera;
	USAffine2D preViewMtx;
	
	if ( this->mCamera ) {
		preViewMtx = this->mCamera->GetWorldToLocalMtx ();
		
		preViewMtx.m [ USAffine2D::C2_R0 ] *= this->mParallax.mX;
		preViewMtx.m [ USAffine2D::C2_R1 ] *= this->mParallax.mY;
	}
	else {
		preViewMtx.Ident ();
	}
	
	USCanvas::BeginDrawing ( viewport, camera, preViewMtx );
	
	if ( this->mShowDebugLines ) {
		
		#if USE_CHIPMUNK
			if ( this->mCpSpace ) {
				this->mCpSpace->DrawDebug ();
				drawBuffer.Flush ();
				drawBuffer.Reset ();
			}
		#endif
		
		#if USE_BOX2D
			if ( this->mBox2DWorld ) {
				this->mBox2DWorld->DrawDebug ();
				drawBuffer.Flush ();
				drawBuffer.Reset ();
			}
		#endif
	}
	
	if ( this->mPartition ) {
		
		USViewQuad viewQuad;
		viewQuad.Init ();
		
		this->mPartition->GatherProps ( viewQuad.mBounds, 0, MOAIDeck::CAN_DRAW | MOAIDeck::CAN_DRAW_DEBUG );
		u32 totalResults = this->mPartition->GetTotalResults ();
		if (( !totalResults ) || ( totalResults > MAX_RENDERABLES )) return;
		
		// initialize the sort buffer
		USRadixKey16 < MOAIProp* > key [ MAX_RENDERABLES ];
		USRadixKey16 < MOAIProp* > swap [ MAX_RENDERABLES ];
		
		u32 count = 0;
		while ( MOAIProp* prim = this->mPartition->PopResult ()) {
			s16 priority = ( s16 )prim->GetPriority ();
			key [ count ].mKey = (( priority ^ 0x8000 ) | ( priority & 0x7fff ));
			key [ count ].mData = prim;
			count++;
		}

		// sort
		USRadixKey16 < MOAIProp* >* sort = RadixSort16 < MOAIProp* >( key, swap, count );

		// render the sorted list
		for ( u32 i = 0; i < count; ++i ) {
			MOAIProp* prim = sort [ i ].mData;
			prim->Draw ();
			prim->DrawDebug ();
		}
	}
	
	// render the debug lines
	if ( this->mShowDebugLines ) {
		drawBuffer.Flush ();
		MOAIDebugLines::Get ().Draw ();
		drawBuffer.Flush ();
	}
}

//----------------------------------------------------------------//
float MOAILayer2D::GetFitting ( USRect& worldRect, float hPad, float vPad ) {

	if ( !( this->mCamera && this->mViewport )) return 1.0f;

	USRect viewRect = this->mViewport->GetRect ();
	
	float hFit = ( viewRect.Width () - ( hPad * 2 )) / worldRect.Width ();
	float vFit = ( viewRect.Height () - ( vPad * 2 )) / worldRect.Height ();
	
	return ( hFit < vFit ) ? hFit : vFit;
}

//----------------------------------------------------------------//
u32 MOAILayer2D::GetLocalFrame ( USRect& frame ) {
	
	if ( this->mViewport ) {
		frame = this->mViewport->GetRect ();
		return MOAIProp::BOUNDS_OK;
	}
	return MOAIProp::BOUNDS_EMPTY;
}

//----------------------------------------------------------------//
void MOAILayer2D::GetWndToWorldMtx ( USAffine2D& wndToWorld ) {

	if ( this->mViewport ) {
		
		USCamera2D camera;
		USCanvas::GetWndToWorldMtx ( *this->mViewport, camera, wndToWorld );
		
		if ( this->mCamera ) {
			USAffine2D preViewInv = this->mCamera->GetLocalToWorldMtx ();
			wndToWorld.Append ( preViewInv );
		}
	}
	else {
		wndToWorld.Ident ();
	}
}

//----------------------------------------------------------------//
void MOAILayer2D::GetWorldToWndMtx ( USAffine2D& worldToWnd ) {

	if ( this->mCamera && this->mViewport ) {
		
		USCamera2D camera;
		USCanvas::GetWorldToWndMtx ( *this->mViewport, camera, worldToWnd );
		
		if ( this->mCamera ) {
			USAffine2D preViewInv = this->mCamera->GetWorldToLocalMtx ();
			worldToWnd.Prepend ( preViewInv );
		}
	}
	else {
		worldToWnd.Ident ();
	}
}

//----------------------------------------------------------------//
MOAILayer2D::MOAILayer2D () :
	mParallax ( 1.0f, 1.0f ),
	mShowDebugLines ( true ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIProp2D )
	RTTI_END
	
	this->SetMask ( MOAIDeck::CAN_DRAW | MOAIDeck::CAN_DRAW_DEBUG );
}

//----------------------------------------------------------------//
MOAILayer2D::~MOAILayer2D () {
}

//----------------------------------------------------------------//
void MOAILayer2D::RegisterLuaClass ( USLuaState& state ) {

	MOAIProp2D::RegisterLuaClass ( state );
}

//----------------------------------------------------------------//
void MOAILayer2D::RegisterLuaFuncs ( USLuaState& state ) {
	
	MOAIProp2D::RegisterLuaFuncs ( state );
	
	LuaReg regTable [] = {
		{ "getFitting",				_getFitting },
		{ "getPartition",			_getPartition },
		{ "insertPrim",				_insertPrim },
		{ "removePrim",				_removePrim },
		{ "setBox2DWorld",			_setBox2DWorld },
		{ "setCamera",				_setCamera },
		{ "setCpSpace",				_setCpSpace },
		{ "setParallax",			_setParallax },
		{ "setPartition",			_setPartition },
		{ "setViewport",			_setViewport },
		{ "showDebugLines",			_showDebugLines },
		{ "wndToWorld",				_wndToWorld },
		{ "worldToWnd",				_worldToWnd },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
STLString MOAILayer2D::ToString () {

	STLString repr( MOAIProp2D::ToString () );

	PRETTY_PRINT ( repr, mCamera )
	PRETTY_PRINT ( repr, mViewport )
	PRETTY_PRINT ( repr, mPartition )

	return repr;
}
