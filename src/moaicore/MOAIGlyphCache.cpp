// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <contrib/utf8.h>
#include <moaicore/MOAIBitmapFontRipper.h>
#include <moaicore/MOAIDataBuffer.h>
#include <moaicore/MOAIGlyphCache.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIGlyphCachePage.h>
#include <moaicore/MOAIImage.h>
#include <moaicore/MOAIImageTexture.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAITextureBase.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIGlyphCache::_defrag ( lua_State* L ) {
	UNUSED ( L );
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIGlyphCache::_getImage ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGlyphCache, "U" )

	MOAIImage* image = self->GetImage ();
	state.Push ( image );
	return 1;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIGlyphCache::_setImage ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIGlyphCache, "UU" )

	MOAIImage* image = state.GetLuaObject < MOAIImage >( 2 );
	if ( image ) {
		self->SetImage ( *image );
	}
	return 0;
}

//================================================================//
// MOAIGlyphCache
//================================================================//

//----------------------------------------------------------------//
void MOAIGlyphCache::ClearPages () {

	for ( u32 i = 0; i < this->mPages.Size (); ++i ) {
		delete this->mPages [ i ];
	}
	this->mPages.Clear ();
}

//----------------------------------------------------------------//
MOAIImage* MOAIGlyphCache::GetGlyphImage ( MOAIGlyph& glyph ) {

	assert ( glyph.mCacheKey < this->mPages.Size ());
	return this->mPages [ glyph.mCacheKey ]->mImageTexture;
}

//----------------------------------------------------------------//
MOAIImage* MOAIGlyphCache::GetImage () {

	u32 totalPages = this->mPages.Size ();
	if ( !totalPages ) return 0;

	u32 width = 0;
	u32 height = 0;

	for ( u32 i = 0; i < totalPages; ++i ) {
		MOAIImage& srcImage = *this->mPages [ i ]->mImageTexture;
		
		width = srcImage.GetWidth ();
		height += srcImage.GetHeight ();
	}
	
	MOAIImage& srcImage0 = *this->mPages [ 0 ]->mImageTexture;
	MOAIImage* image = new MOAIImage ();
	
	image->Init (
		width,
		height,
		srcImage0.GetColorFormat (),
		srcImage0.GetPixelFormat ()
	);
	
	u32 y = 0;
	for ( u32 i = 0; i < totalPages; ++i ) {
		MOAIImage& srcImage = *this->mPages [ i ]->mImageTexture;
		
		u32 copyHeight = srcImage.GetHeight ();
		image->CopyBits ( srcImage, 0, 0, 0, y, width, copyHeight );
		y += copyHeight;
	}
	
	return image;
}

//----------------------------------------------------------------//
MOAIGlyphCache::MOAIGlyphCache () :
	mFont ( 0 ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIGlyphCache::~MOAIGlyphCache () {
}

//----------------------------------------------------------------//
void MOAIGlyphCache::PlaceGlyph ( MOAIGlyph& glyph ) {

	glyph.mCacheKey = BAD_KEY;
	
	for ( u32 i = 0; i < this->mPages.Size (); ++i ) {
		MOAIGlyphCachePage* page = this->mPages [ i ];
		MOAISpan < MOAIGlyph* >* span = page->Alloc ( glyph );
		if ( span ) {
			glyph.mCacheKey = i;
			return;
		}
	}
	
	u32 pageID = this->mPages.Size ();
	this->mPages.Resize ( pageID + 1 );
	
	MOAIGlyphCachePage* page = new MOAIGlyphCachePage ();
	this->mPages [ pageID ] = page;

	page->Alloc ( glyph );
	glyph.mCacheKey = pageID;
}

//----------------------------------------------------------------//
void MOAIGlyphCache::RegisterLuaClass ( MOAILuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIGlyphCache::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "defrag",						_defrag },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIGlyphCache::RemoveGlyph ( MOAIGlyph& glyph ) {
	UNUSED ( glyph );
}

//----------------------------------------------------------------//
void MOAIGlyphCache::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIGlyphCache::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIGlyphCache::SetImage ( MOAIImage& image ) {

	this->ClearPages ();

	u32 width = image.GetWidth ();
	u32 height = image.GetHeight ();

	if ( !( width && height )) return;

	u32 totalPages = ( height / width ) + 1;
	this->mPages.Init ( totalPages );
	
	u32 y = 0;
	for ( u32 i = 0; i < totalPages; ++i ) {
		MOAIImageTexture* page = new MOAIImageTexture ();
		
		u32 pageHeight = height - y;
		pageHeight = pageHeight > width ? width : pageHeight;
		
		page->Init (
			width,
			pageHeight,
			image.GetColorFormat (),
			image.GetPixelFormat ()
		);
		
		page->CopyBits ( image, 0, y, 0, 0, width, pageHeight );
		page->Invalidate ();
		y += pageHeight;
	}
}
