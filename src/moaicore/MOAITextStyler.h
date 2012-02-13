// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAITEXTSTYLER_H
#define	MOAITEXTSTYLER_H

class MOAIAnimCurve;
class MOAIFont;
class MOAITextStyleMap;
class MOAITextStyle;
class MOAITextStyleSet;

//================================================================//
// MOAITextStyler
//================================================================//
class MOAITextStyler {
private:

	// max color hex digits
	static const u32 COLOR_MAX = 8;

	// style parser states
	enum {
		DONE,
		
		STYLE_START,
		STYLE_BODY,
		STYLE_FINISH,
		STYLE_ABORT,
		
		STYLE_NAME_START,
		STYLE_NAME_FINISH,
		
		STYLE_POP_START,
		STYLE_POP_FINISH,
		
		TOKEN_TEXT,
		
		COLOR_START,
		COLOR_BODY,
		COLOR_FINISH,
	};

	// color sizes
	enum {
		COLOR_GRAY_16		= 1,
		COLOR_GRAY_256		= 2,
		COLOR_RGB_16		= 3,
		COLOR_RGBA_16		= 4,
		COLOR_UNKNOWN		= 5,
		COLOR_RGB_256		= 6,
		COLOR_RGBA_256_16	= 7,
		COLOR_RGBA_256		= 8,
	};

	int					mIdx;
	int					mPrev;
	
	int					mTokenBase;
	int					mTokenTop;
	
	cc8*				mStr;
	MOAITextStyleMap*	mStyleMap;
	MOAITextStyleSet*	mStyleSet;

	MOAITextStyle**		mStyleStack;
	u32					mStyleStackTop;

	MOAITextStyle*		mCurrentStyle;

	static const u32 STYLE_STACK_SIZE = 256;

	//----------------------------------------------------------------//
	void			FinishToken			();
	u32				GetChar				();
	static u8		HexToByte			( u32 c );
	static bool		IsWhitespace		( u32 c );
	u32				PackColor			( const u8* color, u32 colorSize );
	void			Parse				();
	bool			ParseStyle			();
	void			PopStyle			();
	void			PushStyle			( MOAITextStyle* style );
	void			Style				( MOAITextStyleMap& styleMap, MOAITextStyleSet& styleSet, cc8* str );
	void			UngetChar			();

public:

	friend class MOAITextStyleMap;

	//----------------------------------------------------------------//
					MOAITextStyler			();
					~MOAITextStyler			();
};

#endif
