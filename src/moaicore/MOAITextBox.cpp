// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIAnimCurve.h>
#include <moaicore/MOAIDeck.h>
#include <moaicore/MOAIDebugLines.h>
#include <moaicore/MOAIFont.h>
#include <moaicore/MOAITextBox.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	clearCurves
	@text	Removes all of the animation curves currently bound to this text object.

	@in		MOAITextBox self
	@out	nil
*/
int MOAITextBox::_clearCurves ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "U" )

	self->ClearCurves ();

	return 0;
}

//----------------------------------------------------------------//
/**	@name	more
	@text	Returns whether there are additional pages of text below the cursor position that are not visible on the screen.

	@in		MOAITextBox self
	@out	boolean isMore				If there is additional text below the cursor that is not visible on the screen due to clipping.
*/
int MOAITextBox::_more ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "U" )
	
	bool more = self->More ();
	lua_pushboolean ( L, more );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	nextPage
	@text	Advances to the next page of text (if any) or wraps to the start of the text (if at end).

	@in		MOAITextBox self
	@out	nil
*/
int MOAITextBox::_nextPage ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "U" )

	bool reveal = state.GetValue < bool >( 2, true );
	self->NextPage ( reveal );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	reserveCurves
	@text	Reserves a set of IDs for animation curves to be binding to this text object.  See setCurves.

	@in		MOAITextBox self
	@in		number nCurves
	@out	nil
*/
int MOAITextBox::_reserveCurves ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UN" )

	u32 total = state.GetValue < u32 >( 2, 0 );
	self->ReserveCurves ( total );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	revealAll
	@text	Displays as much text as will fit in the text box.

	@in		MOAITextBox self
	@out	nil
*/
int MOAITextBox::_revealAll ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "U" )
	
	self->mReveal = REVEAL_ALL;
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setAlignment
	@text	Sets the alignment of the text in the text box.

	@in		MOAITextBox self
	@in		enum mAlignment				Can be one of LEFT_JUSTIFY, CENTER_JUSTIFY or RIGHT_JUSTIFY.
	@out	nil
*/
int MOAITextBox::_setAlignment ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UN" )

	u32 alignment = state.GetValue < u32 >( 2, USFont::LEFT_JUSTIFY );
	self->mJustify = alignment;

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setCurve
	@text	Binds an animation curve to the text, where the Y value of the curve indicates the text offset.

	@in		MOAITextBox self
	@in		number curveID				The ID of the curve within this text object.
	@in		MOAIAnimCurve curve			The MOAIAnimCurve to bind to.
	@out	nil
*/
int MOAITextBox::_setCurve ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UNU" )
	
	u32 index = state.GetValue < u32 >( 2, 0 ) - 1;
	
	MOAIAnimCurve* curve = state.GetLuaObject < MOAIAnimCurve >( 3 );
	if ( !curve ) return 0;

	self->SetCurve ( index, curve );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFont
	@text	Sets the specified font to be used to render text within this text object.

	@in		MOAITextBox self
	@in		MOAIFont font				The MOAIFont to be used as the font for this text object.
	@out	nil
*/
int MOAITextBox::_setFont ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UU" )

	MOAIFont* font = state.GetLuaObject < MOAIFont >( 2 );
	if ( !font ) return 0;
	
	self->SetFont ( font );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setParent
	@text	Sets this text object as a child of the specified parent transform, prim or layout.

	@in		MOAITextBox self
	@in		MOAITransform parent		The MOAITransform that will be the parent of this text object.
	@out	nil
*/
int MOAITextBox::_setParent ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UU" )

	MOAITransform* parent = state.GetLuaObject < MOAITransform >( 2 );
	if ( !parent ) return 0;
	
	self->SetParent ( parent );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setRect
	@text	Sets the rectangular area for this text box.

	@in		MOAITextBox self
	@in		number x1					The X coordinate of the rect's upper-left point.
	@in		number y1					The Y coordinate of the rect's upper-left point.
	@in		number x2					The X coordinate of the rect's lower-right point.
	@in		number y2					The Y coordinate of the rect's lower-right point.
	@out	nil
*/
int MOAITextBox::_setRect ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UNNNN" )

	float left		= state.GetValue < float >( 2, 0.0f );
	float top		= state.GetValue < float >( 3, 0.0f );
	float right		= state.GetValue < float >( 4, 0.0f );
	float bottom	= state.GetValue < float >( 5, 0.0f );

	self->SetRect ( left, top, right, bottom );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setReveal
	@text	Sets the number of renderable characters to be shown.  Can range from 0 to any value; values greater than the number of renderable characters in the current text will be ignored.

	@in		MOAITextBox self
	@in		number reveal				The number of renderable characters (i.e. not whitespace) to be shown.
	@out	nil
*/
int MOAITextBox::_setReveal ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UN" )

	self->mReveal = state.GetValue < u32 >( 2, self->mReveal );
	self->mSpool = ( float )self->mReveal;

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setSpeed
	@text	Sets the base spool speed used when creating a spooling MOAIAction with the spool() function.

	@in		MOAITextBox self
	@in		number speed				The base spooling speed.
	@out	nil
*/
int MOAITextBox::_setSpeed ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UN" )
	
	self->mSpeed = state.GetValue < float >( 2, self->mSpeed );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setString
	@text	Sets the text string to be displayed by this textbox.

	@in		MOAITextBox self
	@in		string newStr				The new text string to be displayed.
	@out	nil
*/
int MOAITextBox::_setString ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "US" )

	cc8* text = state.GetValue < cc8* >( 2, "" );
	self->SetText ( text );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setTextSize
	@text	Sets the size of the text to be rendered.  To avoid sampling, this should be the same or smaller than the point size returned by the font (which is different to the size or scale specified when initalizing the font; they are not measured in the same units).

	@in		MOAITextBox self
	@in		number newTextSize			The new size of the text.
	@out	nil
*/
int MOAITextBox::_setTextSize ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UN" )

	float newTextSize = state.GetValue < float >( 2, 0.0f );
	self->SetTextSize ( newTextSize );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setYFlip
	@text	Sets the rendering direction for the text.  Default assumes a window style screen space (positive Y moves down the screen).  Set to true to render text for world style coordinate systems (positive Y moves up the screen).

	@in		MOAITextBox self
	@in		number yFlip				Whether the vertical rendering direction should be inverted.
	@out	nil
*/
int MOAITextBox::_setYFlip ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "UB" )

	self->mYFlip = state.GetValue < bool >( 2, self->mYFlip );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	spool
	@text	Creates a new MOAIAction which when run has the effect of increasing the amount of characters revealed from 0 to the length of the string currently set.  The spool action is automatically added to the root of the action tree, but may be reparented or stopped by the developer.  This function also automatically sets the current number of revealed characters to 0 (i.e. MOAITextBox:setReveal(0)).

	@in		MOAITextBox self
	@in		number yFlip				Whether the vertical rendering direction should be inverted.
	@out	MOAIAction action			The new MOAIAction which spools the text when run.
*/
int MOAITextBox::_spool ( lua_State* L ) {
	LUA_SETUP ( MOAITextBox, "U" )

	self->mReveal = state.GetValue < u32 >( 2, 0 );
	self->mSpool = ( float )self->mReveal;

	self->Start ();

	return 1;
}

//================================================================//
// MOAITextBox
//================================================================//

const float MOAITextBox::DEFAULT_SPOOL_SPEED = 24.0f;

//----------------------------------------------------------------//
void MOAITextBox::ApplyAttrOp ( u32 attrID, USAttrOp& attrOp ) {

	MOAITransform::ApplyAttrOp ( attrID, attrOp );
}

//----------------------------------------------------------------//
void MOAITextBox::ClearCurves () {

	for ( u32 i = 0; i < this->mMOAICurves.Size (); ++i ) {
		this->mMOAICurves [ i ]->Release ();
	}
	this->mMOAICurves.Clear ();
	this->mCurves.Clear ();
}

//----------------------------------------------------------------//
void MOAITextBox::ClearPageInfo () {

	this->mPageSize = 0;
}

//----------------------------------------------------------------//
void MOAITextBox::Draw () {
	
	if ( !this->mFont ) return;
	
	USFont* font = this->mFont->Bind ();
	
	if ( font ) {
	
		USDrawBuffer& drawbuffer = USDrawBuffer::Get ();
		USAffine2D localToWorldMtx = this->GetLocalToWorldMtx ();
		
		if ( this->mYFlip ) {
			
			USAffine2D mtx;
			
			mtx.Scale ( 1.0f, -1.0f );
			localToWorldMtx.Append ( mtx );
			
			mtx.Translate ( 0.0f, ( this->mFrame.mYMin + this->mFrame.mYMax ));
			localToWorldMtx.Append ( mtx );
		}
		
		drawbuffer.SetVtxTransform ( localToWorldMtx );
		
		this->LoadShader ();
		drawbuffer.SetBlendMode ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		
		if ( this->mReveal && ( this->mTextOffset <= this->mTextLength )) {
			this->Layout ();
			this->mFont->Draw ( this->mLayout, this->mReveal );
		}
	}
}

//----------------------------------------------------------------//
void MOAITextBox::DrawDebug () {

	MOAIDebugLines& debugLines = MOAIDebugLines::Get ();
	if ( debugLines.Bind ( MOAIDebugLines::TEXT_BOX )) {
		
		debugLines.SetWorldMtx ( this->GetLocalToWorldMtx ());
		debugLines.SetPenSpace ( MOAIDebugLines::MODEL_SPACE );
		
		debugLines.DrawRect ( this->mFrame );
	}
}

//----------------------------------------------------------------//
u32 MOAITextBox::GetLocalFrame ( USRect& frame ) {

	frame = this->mFrame;
	return MOAIProp::BOUNDS_OK;
}

//----------------------------------------------------------------//
bool MOAITextBox::IsBusy () {

	if ( this->IsActive ()) {
		this->Layout ();
		return ( this->mReveal < this->mLayout.GetTop ());
	}
	return false;
}

//----------------------------------------------------------------//
void MOAITextBox::Layout () {

	if ( this->mPageSize ) return;
	if ( this->mTextOffset > this->mTextLength ) return;
	if ( !this->mFont ) return;
	
	this->mLayout.Reset ();
	
	USTextStyler styler = this->mStyler;
	this->mPageSize = this->mFont->Layout (
		this->mLayout,
		&this->mText [ this->mTextOffset ],
		this->mPoints,
		this->mFrame,
		this->mJustify,
		styler,
		this->mCurves,
		this->mCurves.Size ()
	);
	
	this->mNextStyler = styler;
}

//----------------------------------------------------------------//
MOAITextBox::MOAITextBox () :
	mText ( "" ),
	mTextLength ( 0 ),
	mTextOffset ( 0 ),
	mJustify ( USFont::LEFT_JUSTIFY ),
	mPoints ( 0 ),
	mPageSize ( 0 ),
	mSpool ( 0.0f ),
	mSpeed ( DEFAULT_SPOOL_SPEED ),
	mReveal ( REVEAL_ALL ),
	mYFlip ( false ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAIProp2D )
		RTTI_EXTEND ( MOAIAction )
	RTTI_END
	
	this->mFrame.Init ( 0.0f, 0.0f, 0.0f, 0.0f ); 
	this->SetMask ( MOAIProp::CAN_DRAW | MOAIProp::CAN_DRAW_DEBUG );
}

//----------------------------------------------------------------//
MOAITextBox::~MOAITextBox () {

	this->ClearCurves ();
}

//----------------------------------------------------------------//
bool MOAITextBox::More () {
	
	this->Layout ();
	u32 offset = this->mTextOffset + this->mPageSize;
	if ( offset >= this->mTextLength ) {
		return false;
	}
	return true;
}

//----------------------------------------------------------------//
void MOAITextBox::NextPage ( bool reveal ) {
	
	this->Layout ();
	
	u32 offset = this->mTextOffset + this->mPageSize;
	if ( offset >= this->mTextLength ) {
		offset = 0;
	}
	this->mTextOffset = offset;
	this->mStyler = this->mNextStyler;
	
	this->ClearPageInfo ();
	this->mReveal = reveal ? REVEAL_ALL : 0;
	this->mSpool = 0.0f;
}

//----------------------------------------------------------------//
void MOAITextBox::OnUpdate ( float step ) {
	
	this->mSpool += ( this->mSpeed * step );
	this->mReveal = ( u32 )this->mSpool;
}

//----------------------------------------------------------------//
void MOAITextBox::RegisterLuaClass ( USLuaState& state ) {

	MOAIProp2D::RegisterLuaClass ( state );
	MOAIAction::RegisterLuaClass ( state );

	state.SetField ( -1, "LEFT_JUSTIFY", ( u32 )USFont::LEFT_JUSTIFY );
	state.SetField ( -1, "CENTER_JUSTIFY", ( u32 )USFont::CENTER_JUSTIFY );
	state.SetField ( -1, "RIGHT_JUSTIFY", ( u32 )USFont::RIGHT_JUSTIFY );
}

//----------------------------------------------------------------//
void MOAITextBox::RegisterLuaFuncs ( USLuaState& state ) {
	
	MOAIProp2D::RegisterLuaFuncs ( state );
	MOAIAction::RegisterLuaFuncs ( state );
	
	LuaReg regTable [] = {
		{ "clearCurves",		_clearCurves },
		{ "more",				_more },
		{ "nextPage",			_nextPage },
		{ "reserveCurves",		_reserveCurves },
		{ "revealAll",			_revealAll },
		{ "setAlignment",		_setAlignment },
		{ "setCurve",			_setCurve },
		{ "setFont",			_setFont },
		{ "setRect",			_setRect },
		{ "setReveal",			_setReveal },
		{ "setString",			_setString },
		{ "setTextSize",		_setTextSize },
		{ "setYFlip",			_setYFlip },
		{ "spool",				_spool },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITextBox::ReserveCurves ( u32 total ) {

	this->ClearCurves ();
	
	this->mMOAICurves.Init ( total );
	this->mMOAICurves.Fill ( 0 );
	
	this->mCurves.Init ( total );
	this->mCurves.Fill ( 0 );
}

//----------------------------------------------------------------//
void MOAITextBox::SerializeIn ( USLuaState& state, USLuaSerializer& serializer ) {

	MOAIProp2D::SerializeIn ( state, serializer );
	MOAIAction::SerializeIn ( state, serializer );
}

//----------------------------------------------------------------//
void MOAITextBox::SerializeOut ( USLuaState& state, USLuaSerializer& serializer ) {

	MOAIProp2D::SerializeOut ( state, serializer );
	MOAIAction::SerializeOut ( state, serializer );
}

//----------------------------------------------------------------//
void MOAITextBox::SetCurve ( u32 idx, MOAIAnimCurve* curve ) {

	if ( idx > this->mMOAICurves.Size ()) return;

	curve->Retain ();
	
	if ( this->mMOAICurves [ idx ]) {
		this->mMOAICurves [ idx ]->Release ();
	}
	
	this->mMOAICurves [ idx ] = curve;
	this->mCurves [ idx ] = curve;
}

//----------------------------------------------------------------//
void MOAITextBox::SetFont ( MOAIFont* font ) {

	this->mFont = font;
	this->ClearPageInfo ();
}

//----------------------------------------------------------------//
void MOAITextBox::SetRect ( float left, float top, float right, float bottom ) {

	this->mFrame.Init ( left, top, right, bottom );
	this->ClearPageInfo ();
}

//----------------------------------------------------------------//
void MOAITextBox::SetText ( cc8* text ) {

	this->mStyler.Reset ();

	this->mText = text;
	this->mTextLength = ( u32 )this->mText.length ();
	this->mTextOffset = 0;
	
	this->ClearPageInfo ();
	this->mReveal = REVEAL_ALL;
	this->mSpool = 0.0f;
}

//----------------------------------------------------------------//
void MOAITextBox::SetTextSize( float newSize ) {

	this->mPoints = newSize;
	this->ClearPageInfo ();
}

//----------------------------------------------------------------//
STLString MOAITextBox::ToString () {

	STLString repr;

	// TODO
	return repr;
}
