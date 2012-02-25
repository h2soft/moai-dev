// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <contrib/utf8.h>
#include <moaicore/MOAIDataBuffer.h>
#include <moaicore/MOAIGlyphCacheBase.h>
#include <moaicore/MOAIFont.h>
#include <moaicore/MOAIFontReader.h>
#include <moaicore/MOAIGfxDevice.h>
#include <moaicore/MOAIGlyphCacheBase.h>
#include <moaicore/MOAIImage.h>
#include <moaicore/MOAIImageTexture.h>
#include <moaicore/MOAILogMessages.h>
#include <moaicore/MOAITextureBase.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFont::_getFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	state.Push ( self->mFlags );
	return 1;
}

//----------------------------------------------------------------//
/**	@name	load
	@text	Sets the font file for use when loading glyphs.

	@in		MOAIFont self
	@in		string filename			The path to the TTF file to load.
	@out	nil
*/
int MOAIFont::_load ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "US" )

	cc8* filename	= state.GetValue < cc8* >( 2, "" );
	self->Init ( filename );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	preloadGlyphs
	@text	Loads and caches glyphs for quick access later.

	@in		MOAIFont self
	@in		string charCodes		A string which defines the characters found in the this->
	@in		number points			The point size to be rendered onto the internal texture.
	@opt	number dpi				The device DPI (dots per inch of device screen). Default value is 72 (points same as pixels).
	@out	nil
*/
int MOAIFont::_preloadGlyphs ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "USN" )

	cc8* charCodes	= state.GetValue < cc8* >( 2, "" );
	float points	= state.GetValue < float >( 3, 0 );
	float dpi		= state.GetValue < float >( 4, DPI );
	
	float size = POINTS_TO_PIXELS ( points, dpi );
	
	int idx = 0;
	while ( charCodes [ idx ]) {
		u32 c = u8_nextchar ( charCodes, &idx );
		self->AffirmGlyph ( size, c );
	}
	self->ProcessGlyphs ();
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFont::_rebuildKerningTables ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	
	if ( self->mFontReader ) {
	
		if ( state.IsType ( 2, LUA_TNUMBER )) {
			
			float points	= state.GetValue < float >( 2, 0 );
			float dpi		= state.GetValue < float >( 3, DPI );
			
			float size = POINTS_TO_PIXELS ( points, dpi );
			self->RebuildKerning ( size );
		}
		else {
			self->RebuildKerning ();
		}
	}
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFont::_setFlags ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	self->mFlags = state.GetValue < u32 >( 2, DEFAULT_FLAGS );
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFont::_setFontReader ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	self->mFontReader.Set ( *self, state.GetLuaObject < MOAIFontReader >( 2 ));
	return 0;
}

//----------------------------------------------------------------//
// TODO: doxygen
int MOAIFont::_setGlyphCache ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFont, "U" )
	self->mGlyphCache.Set ( *self, state.GetLuaObject < MOAIGlyphCacheBase >( 2 ));
	return 0;
}

//================================================================//
// MOAIFont
//================================================================//

//----------------------------------------------------------------//
void MOAIFont::AffirmGlyph ( float points, u32 c ) {

	MOAIGlyphSet& glyphDeck = this->mGlyphDecks [ points ];
	glyphDeck.mPoints = points;
	glyphDeck.AffirmGlyph ( c );
}

//----------------------------------------------------------------//
// iterate through the pending glyphs in each set and attempt to
// update them to match target - i.e. metrics or metrics and bitmap
void MOAIFont::BuildKerning ( MOAIGlyph* glyphs, MOAIGlyph* pendingGlyphs ) {

	if ( !this->mFontReader->HasKerning ()) return;
	MOAIKernVec kernTable [ MOAIGlyph::MAX_KERN_TABLE_SIZE ];

	// iterate over the orignal glyphs and add kerning info for new glyphs
	for ( MOAIGlyph* glyphIt = glyphs; glyphIt; glyphIt = glyphIt->mNext ) {
		MOAIGlyph& glyph = *glyphIt;
		
		u32 kernTableSize = 0;
		u32 oldTableSize = glyph.mKernTable.Size ();
		
		// iterate over just the new glyphs; check each one against olf glyphs for kerning info
		for ( MOAIGlyph* glyphIt2 = pendingGlyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			// skip if glyph is already in old glyph's kerning table
			// may happen if glyphs are purged and then re-added
			bool unknown = true;
			for ( u32 i = 0; i < oldTableSize; ++i ) {
				if ( glyph.mKernTable [ i ].mName == glyph2.mCode ) {
					unknown = false;
					break;
				}
			} 
			
			if ( unknown ) {
				MOAIKernVec kernVec;
				if ( this->mFontReader->GetKernVec ( glyph, glyph2, kernVec )) {
					assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
					kernTable [ kernTableSize++ ] = kernVec;
				}
			}
		}
		
		// resize the old kerning table and copy in the new kern vecs (if any)
		if ( kernTableSize ) {
			glyph.mKernTable.Resize ( oldTableSize + kernTableSize );
			memcpy ( &glyph.mKernTable [ oldTableSize ], kernTable, sizeof ( MOAIKernVec ) * kernTableSize );
		}
	}
	
	// iterate over the new glyphs and add kerning info for all glyphs
	for ( MOAIGlyph* glyphIt = pendingGlyphs; glyphIt; glyphIt = glyphIt->mNext ) {
		MOAIGlyph& glyph = *glyphIt;
		
		u32 kernTableSize = 0;
		
		// iterate over the original glyphs
		for ( MOAIGlyph* glyphIt2 = glyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			MOAIKernVec kernVec;
			if ( this->mFontReader->GetKernVec ( glyph, glyph2, kernVec )) {
				assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
				kernTable [ kernTableSize++ ] = kernVec;
			}
		}
		
		// iterate over the new glyphs
		for ( MOAIGlyph* glyphIt2 = pendingGlyphs; glyphIt2; glyphIt2 = glyphIt2->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt2;
			
			MOAIKernVec kernVec;
			if ( this->mFontReader->GetKernVec ( glyph, glyph2, kernVec )) {
				assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
				kernTable [ kernTableSize++ ] = kernVec;
			}
		}
		
		// init the kern table
		if ( kernTableSize ) {
			glyph.mKernTable.Init ( kernTableSize );
			memcpy ( glyph.mKernTable, kernTable, sizeof ( MOAIKernVec ) * kernTableSize );
		}
	}
}

//----------------------------------------------------------------//
MOAIGlyphSet* MOAIFont::GetGlyphDeck ( float points ) {

	return &this->mGlyphDecks [ points ];
}

//----------------------------------------------------------------//
MOAITextureBase* MOAIFont::GetGlyphTexture ( MOAIGlyph& glyph ) {

	assert ( this->mGlyphCache );
	return this->mGlyphCache->GetGlyphTexture ( glyph );
}

//----------------------------------------------------------------//
void MOAIFont::Init ( cc8* filename ) {

	this->mFilename = filename;
}

//----------------------------------------------------------------//
bool MOAIFont::IsWhitespace ( u32 c ) {

	if ( !c ) return true;
	if ( c == ' ' ) return true;
	if ( c == '\t' ) return true;
	if ( c == '\n' ) return true;
	
	return false;
}

//----------------------------------------------------------------//
MOAIFont::MOAIFont () :
	mFlags ( DEFAULT_FLAGS ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAILuaObject )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIFont::~MOAIFont () {

	this->mFontReader.Set ( *this, 0 );
	this->mGlyphCache.Set ( *this, 0 );
}

//----------------------------------------------------------------//
// iterate through the pending glyphs in each set and attempt to
// update them to match target - i.e. metrics or metrics and bitmap
void MOAIFont::ProcessGlyphs () {

	if ( !this->mFontReader ) return;

	this->mFontReader->OpenFont ( *this );
	
	MOAIFont::GlyphDecksIt glyphDecksIt = this->mGlyphDecks.begin ();
	for ( ; glyphDecksIt != this->mGlyphDecks.end (); ++glyphDecksIt ) {
		MOAIGlyphSet& glyphDeck = glyphDecksIt->second;
		
		// save pointers to the two glyph lists
		MOAIGlyph* glyphs = glyphDeck.mGlyphs;
		MOAIGlyph* pendingGlyphs = glyphDeck.mPending;
		
		// all pending glyphs will be moved to the processed glyphs list
		// so clear the pending glyphs list
		glyphDeck.mPending = 0;
		
		// if no pending glyphs, move on to the next deck
		if ( !pendingGlyphs ) continue;
		
		// get the face metrics
		this->mFontReader->SetFaceSize ( glyphDeck.mPoints );
		this->mFontReader->GetFaceMetrics ( glyphDeck );
		
		// build kerning tables (if face has kerning info)
		if (( this->mFlags & FONT_AUTOLOAD_KERNING ) && this->mFontReader->HasKerning ()) {
			this->BuildKerning ( glyphs, pendingGlyphs );
		}
		
		//----------------------------------------------------------------//
		// render the new glyphs and move them to the processed list
		for ( MOAIGlyph* glyphIt = pendingGlyphs; glyphIt; ) {
			MOAIGlyph& glyph = *glyphIt;
			glyphIt = glyphIt->mNext;
			
			// move the glyph into the processed glyphs list
			glyph.mNext = glyphDeck.mGlyphs;
			glyphDeck.mGlyphs = &glyph;
			
			this->mFontReader->RenderGlyph ( *this, glyph );
		}
	}

	this->mFontReader->CloseFont ();
}

//----------------------------------------------------------------//
void MOAIFont::RebuildKerning () {

	if ( !this->mFontReader ) return;
	if ( !this->mFontReader->HasKerning ()) return;
	if ( !this->mGlyphDecks.size ()) return;

	this->mFontReader->OpenFont ( *this );
	
	MOAIFont::GlyphDecksIt glyphDecksIt = this->mGlyphDecks.begin ();
	for ( ; glyphDecksIt != this->mGlyphDecks.end (); ++glyphDecksIt ) {
		MOAIGlyphSet& glyphDeck = glyphDecksIt->second;
		this->RebuildKerning ( glyphDeck );
	}
	
	this->mFontReader->CloseFont ();
}

//----------------------------------------------------------------//
void MOAIFont::RebuildKerning ( float points ) {

	if ( !this->mFontReader ) return;
	if ( !this->mFontReader->HasKerning ()) return;
	if ( !this->mGlyphDecks.contains ( points )) return;
	
	this->mFontReader->OpenFont ( *this );
	
	MOAIGlyphSet& glyphDeck = this->mGlyphDecks [ points ];
	this->RebuildKerning ( glyphDeck );
	
	this->mFontReader->CloseFont ();
}

//----------------------------------------------------------------//
void MOAIFont::RebuildKerning ( MOAIGlyphSet& glyphDeck ) {
	
	MOAIKernVec kernTable [ MOAIGlyph::MAX_KERN_TABLE_SIZE ];
	
	// get the face metrics
	this->mFontReader->SetFaceSize ( glyphDeck.mPoints );

	// iterate over the orignal glyphs and add kerning info for new glyphs
	for ( MOAIGlyph* glyphIt = glyphDeck.mGlyphs; glyphIt; glyphIt = glyphIt->mNext ) {
		MOAIGlyph& glyph = *glyphIt;

		u32 kernTableSize = 0;
		
		// iterate over just the new glyphs; check each one against old glyphs for kerning info
		for ( MOAIGlyph* glyphIt = glyphDeck.mGlyphs; glyphIt; glyphIt = glyphIt->mNext ) {
			MOAIGlyph& glyph2 = *glyphIt;
			
			MOAIKernVec kernVec;
			if ( this->mFontReader->GetKernVec ( glyph, glyph2, kernVec )) {
				assert ( kernTableSize < MOAIGlyph::MAX_KERN_TABLE_SIZE );
				kernTable [ kernTableSize++ ] = kernVec;
			}
		}
		
		// init (or clear) the kern table
		glyph.mKernTable.Resize ( kernTableSize );
		
		// copy in the new kern vecs (if any)
		if ( kernTableSize ) {
			memcpy ( glyph.mKernTable, kernTable, sizeof ( MOAIKernVec ) * kernTableSize );
		}
	}
}

//----------------------------------------------------------------//
void MOAIFont::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "DEFAULT_FLAGS",			( u32 )DEFAULT_FLAGS );
	state.SetField ( -1, "FONT_AUTOLOAD_KERNING",	( u32 )FONT_AUTOLOAD_KERNING );
}

//----------------------------------------------------------------//
void MOAIFont::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "getFlags",					_getFlags },
		{ "load",						_load },
		{ "preloadGlyphs",				_preloadGlyphs },	
		{ "rebuildKerningTables",		_rebuildKerningTables },
		{ "setFlags",					_setFlags },
		{ "setFontReader",				_setFontReader },
		{ "setGlyphCache",				_setGlyphCache },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFont::SerializeIn ( MOAILuaState& state, MOAIDeserializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

//----------------------------------------------------------------//
void MOAIFont::SerializeOut ( MOAILuaState& state, MOAISerializer& serializer ) {
	UNUSED ( state );
	UNUSED ( serializer );
}

