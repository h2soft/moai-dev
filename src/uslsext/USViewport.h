// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef GFX_VIEWPORT_H
#define GFX_VIEWPORT_H

#include <uslsext/USMatrix2D.h>
#include <uslsext/USMatrix3D.h>

//================================================================//
// USViewport
//================================================================//
class USViewport :
	public USRect {
private:

	bool		mXScale;
	bool		mYScale;
	
	USVec2D		mScale;
	USVec2D		mOffset;
	float		mRotation;

public:
	
	friend class USCanvas;
	
	//----------------------------------------------------------------//
	float				GetAspect			();
	float				GetInvAspect		();
	USRect				GetRect				();
	USVec2D				GetScale			();
	void				SetOffset			( float xOffset, float yOffset );
	void				SetRotation			( float degrees );
	void				SetScale			( float xScale, float yScale );
						USViewport			();
};

#endif
