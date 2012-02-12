// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFONT_H
#define	MOAIFONT_H

#include <moaicore/MOAIGlyphDeck.h>
#include <moaicore/MOAILua.h>
#include <moaicore/MOAISpanList.h>

class MOAIGlyph;

//================================================================//
// MOAIFont
//================================================================//
class MOAIFont :
	public MOAILuaObject {
private:

	MOAIGlyphPage* mPages;

	STLString	mFilename;
	
	// for now
	typedef STLMap < float, MOAIGlyphDeck >::iterator GlyphSetsIt;
	STLMap < float, MOAIGlyphDeck > mGlyphSets;

	//----------------------------------------------------------------//
	MOAISpan < MOAIGlyph* >*	Alloc	( MOAIGlyph& glyph );

public:
	
	//----------------------------------------------------------------//
	void			AffirmGlyphs			( float points, cc8* chars, int size );
	void			Init					( cc8* filename );
	void			LoadGlyphMetrics		();
	MOAIGlyph*		GetGlyphForChar			( u32 c );
					MOAIFont				();
					~MOAIFont				();
	void			RenderGlyphs			();
	void			WritePages				();
};

#endif
