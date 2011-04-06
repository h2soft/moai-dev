// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moaicore/MOAIDataBuffer.h>
#include <moaicore/MOAIGrid.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAITexture.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	bind
	@text	Try to force the shader to perform its load.
	
	@in		MOAITexture self
	@out	nil
*/
int MOAITexture::_bind ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITexture, "U" )
	
	self->Bind ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	getSize
	@text	Returns the width and height of the texture's source image.
			Avoid using the texture width and height to compute UV
			coordinates from pixels, as this will prevent texture
			resolution swapping.
	
	@in		MOAITexture self
	@out	width
	@out	height
*/
int MOAITexture::_getSize ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITexture, "U" )
	
	lua_pushnumber ( state, self->mDevWidth );
	lua_pushnumber ( state, self->mDevHeight );
	
	return 2;
}

//----------------------------------------------------------------//
/**	@name	load
	@text	Loads a texture from a data buffer or a file.
	
	@in		MOAITexture self
	@in		variant texture		Either a MOAIDataBuffer containing a binary texture or a path to a texture file.
	@opt	number transform	Any bitwise combination of MOAITexture.QUANTIZE, MOAITexture.TRUECOLOR, MOAITexture.PREMULTIPLY_ALPHA
	@out	nil
*/
int MOAITexture::_load ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITexture, "U" )

	MOAIDataBuffer* data = state.GetLuaObject < MOAIDataBuffer >( 2 );
	u32 transform = state.GetValue < u32 >( 3, DEFAULT_TRANSFORM );

	if ( data ) {

		self->Load ( *data, transform );
	}
	else if ( state.IsType( 2, LUA_TSTRING ) ) {

		cc8* filename = lua_tostring ( state, 2 );
		self->Load ( filename, transform );
	}

	return 0;
}

//----------------------------------------------------------------//
/**	@name	release
	@text	Releases any memory associated with the texture.
	
	@in		MOAITexture self
	@out	nil
*/
int MOAITexture::_release ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITexture, "U" )
	
	self->USTexture::Release ();
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFilter
	@text	Set default filtering mode for texture.
	
	@in		MOAITexture self
	@in		number min			One of MOAITexture.GL_LINEAR or MOAITexture.GL_NEAREST.
	@opt	number mag			Defaults to value passed to 'min'.
	@out	nil
*/
int MOAITexture::_setFilter ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITexture, "UN" )

	int min = state.GetValue < int >( 2, GL_LINEAR );
	int mag = state.GetValue < int >( 3, min );

	self->SetFilter ( min, mag );

	return 0;
}

//----------------------------------------------------------------//
/**	@name	setFilter
	@text	Set wrapping mode for texture.
	
	@in		MOAITexture self
	@in		boolean wrap		Texture will wrap if true, clamp if not.
	@out	nil
*/
int MOAITexture::_setWrap ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAITexture, "UB" )
	
	bool wrap = state.GetValue < bool >( 2, false );
	
	self->mWrap = wrap ? GL_REPEAT : GL_CLAMP_TO_EDGE;

	return 0;
}


//================================================================//
// MOAITexture
//================================================================//

//----------------------------------------------------------------//
MOAITexture* MOAITexture::AffirmTexture ( USLuaState& state, int idx ) {

	MOAITexture* texture = state.GetLuaObject < MOAITexture >( idx );
	if ( !texture ) {

		u32 transform = state.GetValue < u32 >( idx + 1, DEFAULT_TRANSFORM );

		if ( state.IsType ( idx, LUA_TUSERDATA )) {
			
			texture = state.GetLuaObject < MOAITexture >( idx );
			MOAIDataBuffer* data = state.GetLuaObject < MOAIDataBuffer >( idx );
			
			if ( data ) {
				texture = new MOAITexture ();
				texture->Load ( *data, transform );
			}
		}
		else if ( state.IsType ( idx, LUA_TSTRING )) {
			
			cc8* filename = lua_tostring ( state, idx );
			texture = new MOAITexture ();
			texture->Load ( filename, transform );
		}
	}
	return texture;
}

//----------------------------------------------------------------//
bool MOAITexture::Bind () {

	USDrawBuffer& drawBuffer = USDrawBuffer::Get ();
	if ( !drawBuffer.BindTexture ( this )) return false;
	USGLQuad::BindVertexFormat ( drawBuffer );

	return true;
}

//----------------------------------------------------------------//
void MOAITexture::Load ( MOAIDataBuffer& data, u32 transform ) {

	this->Init ( data, transform );
	this->SetFilter ( GL_LINEAR, GL_NEAREST );
	this->SetWrap ( GL_REPEAT );
}

//----------------------------------------------------------------//
void MOAITexture::Load ( cc8* filename, u32 transform ) {

	this->mTexturePath = USFileSys::Expand ( filename );

	if ( !USFileSys::CheckFileExists ( this->mTexturePath )) return;
	this->Init ( this->mTexturePath, transform );
	this->SetFilter ( GL_LINEAR, GL_NEAREST );
	this->SetWrap ( GL_REPEAT );
}

//----------------------------------------------------------------//
MOAITexture::MOAITexture () {

	RTTI_SINGLE ( USLuaObject )
}

//----------------------------------------------------------------//
MOAITexture::~MOAITexture () {
}

//----------------------------------------------------------------//
void MOAITexture::RegisterLuaClass ( USLuaState& state ) {
	
	state.SetField ( -1, "FILTER_POINT", ( u32 )GL_NEAREST );
	state.SetField ( -1, "FILTER_BILERP", ( u32 )GL_LINEAR );
	
	//state.SetField ( -1, "POW_TWO", ( u32 )USImageTransform::POW_TWO ); // TODO: still not sold we should offet this 'feature'
	state.SetField ( -1, "QUANTIZE", ( u32 )USImageTransform::QUANTIZE );
	state.SetField ( -1, "TRUECOLOR", ( u32 )USImageTransform::TRUECOLOR );
	state.SetField ( -1, "PREMULTIPLY_ALPHA", ( u32 )USImageTransform::PREMULTIPLY_ALPHA );
}

//----------------------------------------------------------------//
void MOAITexture::RegisterLuaFuncs ( USLuaState& state ) {

	luaL_Reg regTable [] = {
		{ "bind",				_bind },
		{ "getSize",			_getSize },
		{ "load",				_load },
		{ "release",			_release },
		{ "setFilter",			_setFilter },
		{ "setWrap",			_setWrap },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAITexture::SerializeIn ( USLuaState& state, USLuaSerializer& serializer ) {
	UNUSED ( serializer );

	STLString path = state.GetField ( -1, "mPath", "" );
	
	if ( path.size ()) {
		USFilename filename;
		filename.Bless ( path.str ());
		this->Load ( filename.mBuffer, DEFAULT_TRANSFORM ); // TODO: serialization
	}
}

//----------------------------------------------------------------//
void MOAITexture::SerializeOut ( USLuaState& state, USLuaSerializer& serializer ) {
	UNUSED ( serializer );

	STLString path = USFileSys::GetRelativePath ( this->mTexturePath );
	state.SetField ( -1, "mPath", path.str ());
}

//----------------------------------------------------------------//
STLString MOAITexture::ToString () {

	STLString repr;

	PrettyPrint ( repr, "mWidth", GetWidth ());
	PrettyPrint ( repr, "mHeight", GetHeight ());

	return repr;
}
