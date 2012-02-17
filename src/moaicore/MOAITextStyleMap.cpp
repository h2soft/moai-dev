// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <contrib/utf8.h>
#include <moaicore/MOAIFont.h>
#include <moaicore/MOAITextStyle.h>
#include <moaicore/MOAITextStyler.h>
#include <moaicore/MOAITextStyleMap.h>

//================================================================//
// MOAITextStyleMap
//================================================================//

//----------------------------------------------------------------//
u32 MOAITextStyleMap::AffirmStyle ( MOAITextStyle& style ) {

	u32 top = this->mStyles.GetTop ();
	for ( u32 i = 0; i < top; ++i ) {
		if ( this->mStyles [ i ] == &style) {
			return i;
		}
	}
	this->mStyles.Push ( &style );
	return top;
}

//----------------------------------------------------------------//
MOAITextStyleMap::MOAITextStyleMap () {
}

//----------------------------------------------------------------//
MOAITextStyleMap::~MOAITextStyleMap () {
}

//----------------------------------------------------------------//
void MOAITextStyleMap::PushSpan ( int base, int top, MOAITextStyle& style ) {

	this->AffirmStyle ( style );

	MOAITextStyleSpan token;
	
	token.mBase			= base;
	token.mTop			= top;
	token.mStyle		= &style;

	this->Push ( token );
}

//----------------------------------------------------------------//
void MOAITextStyleMap::Tokenize ( MOAITextStyleSet& styleSet, cc8* str ) {

	MOAITextStyler styler;
	styler.Style ( *this, styleSet, str );
	
	u32 top = this->mStyles.GetTop ();
	for ( u32 i = 0; i < top; ++i ) {
		
		MOAITextStyle* style = this->mStyles [ i ];
		MOAIFont* font = style->GetFont ();
		font->UpdateGlyphs ( MOAIGlyph::METRICS_AND_BITMAP );
	}
}
