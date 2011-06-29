// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <aku/AKU-particles.h>
#include <ParticlePresets.h>

//----------------------------------------------------------------//
static float	_lerp					( float x0, float x1, float t );
static void		_linearRender			( float* particle, float* registers, AKUParticleSprite* sprite, float t0, float t1 );

//----------------------------------------------------------------//
float _lerp ( float x0, float x1, float t ) {

	return x0 + (( x1 - x0 ) * t );
}

//----------------------------------------------------------------//
void _linearRender ( float* particle, float* registers, AKUParticleSprite* sprite, float t0, float t1 ) {

	//float linear	= t1;

	sprite->mXLoc	= registers [ 0 ] * t1;
	sprite->mYLoc	= registers [ 1 ] * t1;
	
	sprite->mZRot	= _lerp ( registers [ 2 ], registers [ 3 ], t1 );
	
	sprite->mXScl	= _lerp ( registers [ 4 ], registers [ 5 ], t1 );
	sprite->mYScl	= sprite->mXScl;
	
	float fade		= 1.0f - t1;
	
	sprite->mRed	= fade;
	sprite->mGreen	= fade;
	sprite->mBlue	= fade;
	sprite->mAlpha	= fade;
	
	sprite->mGfxID	= 1;
}

//================================================================//
// ParticlePresets
//================================================================//

//----------------------------------------------------------------//
void ParticlePresets () {
	
	AKUSetParticlePreset ( "ParticlePresets", 0, _linearRender, 6 );
}
