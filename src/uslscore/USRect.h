// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MATH_RECT_H
#define	MATH_RECT_H

#include <uslscore/USFloat.h>
#include <uslscore/USVec2D.h>
#include <uslscore/USVec3D.h>

//================================================================//
// USMetaRect
//================================================================//
template < typename TYPE = float >
class USMetaRect {
public:

	enum {
		kLeft		= 1 << 0,
		kTop		= 1 << 1,
		kRight		= 1 << 2,
		kBottom		= 1 << 3,
	};

	TYPE	mXMin;
	TYPE	mXMax;
	
	TYPE	mYMin;
	TYPE	mYMax;

	//----------------------------------------------------------------//
	TYPE Area () const {
		return this->Width () * this->Height ();
	}

	//----------------------------------------------------------------//
	TYPE Aspect () const {
	
		float height = this->Height ();
		if ( height == 0.0 ) {
			return 0.0;
		}
	
		return ( TYPE )( this->Width () / height );
	}

	//----------------------------------------------------------------//
	bool BigEnough ( TYPE width, TYPE height ) const {

		if (( this->mXMax - this->mXMin ) < width ) return false;
		if (( this->mYMax - this->mYMin ) < height ) return false;
		
		return true;
	}

	//----------------------------------------------------------------//
	void Bless () {

		if ( this->mXMin > this->mXMax ) {
			TYPE temp = this->mXMin;
			this->mXMin = this->mXMax;
			this->mXMax = temp;
		}
		
		if ( this->mYMin > this->mYMax ) {
			TYPE temp = this->mYMin;
			this->mYMin = this->mYMax;
			this->mYMax = temp;
		}
	}

	//----------------------------------------------------------------//
	void Clip ( USMetaRect < TYPE >& rect ) const {

		// Clamp XMin
		if ( rect.mXMin < this->mXMin ) rect.mXMin = this->mXMin;
		if ( rect.mXMin > this->mXMax ) rect.mXMin = this->mXMax;
		
		// Clamp XMax
		if ( rect.mXMax < this->mXMin ) rect.mXMax = this->mXMin;
		if ( rect.mXMax > this->mXMax ) rect.mXMax = this->mXMax;
		
		// Clamp YMin
		if ( rect.mYMin < this->mYMin ) rect.mYMin = this->mYMin;
		if ( rect.mYMin > this->mYMax ) rect.mYMin = this->mYMax;
		
		// Clamp YMax
		if ( rect.mYMax < this->mYMin ) rect.mYMax = this->mYMin;
		if ( rect.mYMax > this->mYMax ) rect.mYMax = this->mYMax;
	}

	//----------------------------------------------------------------//
	void Constrain ( USMetaRect < TYPE >& rect ) const {

		float width = this->Width ();
		float height = this->Height ();
		
		float rectWidth = rect.Width ();
		float rectHeight = rect.Height ();
		
		if ( rectWidth < width ) {
			
			if ( rect.mXMin < this->mXMin ) {
			
				rect.mXMin = this->mXMin;
				rect.mXMax = this->mXMin + rectWidth;
			}
			else if ( rect.mXMax > this->mXMax ) {
			
				rect.mXMin = this->mXMax - rectWidth;
				rect.mXMax = this->mXMax;
			}
			
			
		}
		else {
		
			float xCenter = this->mXMin + ( TYPE )( width * 0.5f );
		
			rect.mXMin = xCenter - ( TYPE )( rectWidth * 0.5f );
			rect.mXMax = xCenter + ( TYPE )( rectWidth * 0.5f );
		}
		
		if ( rectHeight < height ) {
			
			if ( rect.mYMin < this->mYMin ) {
			
				rect.mYMin = this->mYMin;
				rect.mYMax = this->mYMin + rectHeight;
			}
			else if ( rect.mYMax > this->mYMax ) {
			
				rect.mYMin = this->mYMax - rectHeight;
				rect.mYMax = this->mYMax;
			}
		}
		else {
		
			float yCenter = this->mYMin + ( TYPE )( height * 0.5f );
		
			rect.mYMin = yCenter - ( TYPE )( rectHeight * 0.5f );
			rect.mYMax = yCenter + ( TYPE )( rectHeight * 0.5f );
		}
	}

	//----------------------------------------------------------------//
	bool Contains ( const USMetaVec3D < TYPE >& loc ) const {

		if (( loc.mX < this->mXMin ) || ( loc.mX > this->mXMax )) return false;
		if (( loc.mY < this->mYMin ) || ( loc.mY > this->mYMax )) return false;
		
		return true;
	}

	//----------------------------------------------------------------//
	bool Contains ( const USMetaVec2D < TYPE >& loc ) const {

		if (( loc.mX < this->mXMin ) || ( loc.mX > this->mXMax )) return false;
		if (( loc.mY < this->mYMin ) || ( loc.mY > this->mYMax )) return false;
		
		return true;
	}

	//----------------------------------------------------------------//
	bool Contains ( TYPE x, TYPE y ) const {

		if (( x < this->mXMin ) || ( x > this->mXMax )) return false;
		if (( y < this->mYMin ) || ( y > this->mYMax )) return false;
		
		return true;
	}

	//----------------------------------------------------------------//
	bool Contains ( USMetaRect < TYPE >& rect ) const {

		if (( rect.mXMin < this->mXMin ) || ( rect.mXMax > this->mXMax )) return false;
		if (( rect.mYMin < this->mYMin ) || ( rect.mYMax > this->mYMax )) return false;
		
		return true;
	}

	//----------------------------------------------------------------//
	void Deflate ( TYPE size ) {

		this->mXMin += size;
		this->mYMin += size;
		this->mXMax -= size;
		this->mYMax -= size;
	}

	//----------------------------------------------------------------//
	// Centers and fits rect while preserving its aspect ratio
	void FitInside ( USMetaRect < TYPE >& rect ) const {
		
		TYPE fitAspect = rect.Aspect ();
		
		TYPE width = this->Width ();
		TYPE height = this->Height ();
		
		if (( width == 0.0 ) || ( height == 0.0 )) {
			rect.Init ( 0.0, 0.0, 0.0, 0.0 );
			return;
		}
		
		TYPE aspect = width / height;
		
		TYPE fitWidth;
		TYPE fitHeight;
		
		if ( fitAspect >= aspect ) {
			// rect is fatter
			fitWidth = width;
			fitHeight = ( width / fitAspect );
			
		}
		else {
			// rect is thinner
			fitWidth = ( height * fitAspect );
			fitHeight = height;
		}
		
		rect.mXMin = (( this->mXMin + ( width * ( TYPE )0.5 )) - ( fitWidth * ( TYPE )0.5 ));
		rect.mYMin = (( this->mYMin + ( height * ( TYPE )0.5 )) - ( fitHeight * ( TYPE )0.5 ));
		
		rect.mXMax = rect.mXMin + fitWidth;
		rect.mYMax = rect.mYMin + fitHeight;
	}

	//----------------------------------------------------------------//
	// Centers and fits rect while preserving its aspect ratio
	void FitOutside ( USMetaRect < TYPE >& rect ) const {
		
		TYPE fitAspect = rect.Aspect ();
		
		TYPE width = this->Width ();
		TYPE height = this->Height ();
		
		TYPE fitWidth = 0.0;
		TYPE fitHeight = 0.0;
		
		if (( width == 0.0 ) || ( height == 0.0 )) {
			if ( width > 0.0 ) {
				fitWidth = width;
				fitHeight = ( width / fitAspect );
			}
			else if ( height > 0.0 ) {
				fitWidth = ( height * fitAspect );
				fitHeight = height;
			}
			else {
				rect.Init ( 0.0, 0.0, 0.0, 0.0 );
				return;
			}
		}
		else {
		
			TYPE aspect = width / height;
			
			if ( fitAspect >= aspect ) {
				// rect is fatter
				fitWidth = ( height * fitAspect );
				fitHeight = height;
			}
			else {
				// rect is thinner
				fitWidth = width;
				fitHeight = ( width / fitAspect );
			}
		}
		
		rect.mXMin = (( this->mXMin + ( width * ( TYPE )0.5 )) - ( fitWidth * ( TYPE )0.5 ));
		rect.mYMin = (( this->mYMin + ( height * ( TYPE )0.5 )) - ( fitHeight * ( TYPE )0.5 ));
		
		rect.mXMax = rect.mXMin + fitWidth;
		rect.mYMax = rect.mYMin + fitHeight;
	}

	//----------------------------------------------------------------//
	void FlipX () {
	
		TYPE temp = this->mXMin;
		this->mXMin = this->mXMax;
		this->mXMax = temp;
	}

	//----------------------------------------------------------------//
	void FlipY () {
	
		TYPE temp = this->mYMin;
		this->mYMin = this->mYMax;
		this->mYMax = temp;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void GetCenter ( USMetaVec2D < PARAM_TYPE >& center ) const {

		center.mX = ( PARAM_TYPE )this->mXMin + (( PARAM_TYPE )( this->mXMax - this->mXMin ) / 2 );
		center.mY = ( PARAM_TYPE )this->mYMin + (( PARAM_TYPE )( this->mYMax - this->mYMin ) / 2 );
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void GetCenter ( USMetaVec3D < TYPE >& center ) const {

		center.mX = ( PARAM_TYPE )this->mXMin + (( PARAM_TYPE )( this->mXMax - this->mXMin ) / 2 );
		center.mY = ( PARAM_TYPE )this->mYMin + (( PARAM_TYPE )( this->mYMax - this->mYMin ) / 2 );
		center.mZ = 0;
	}

	//----------------------------------------------------------------//
	bool GetIntersection ( USMetaVec2D < TYPE >& loc, USMetaVec2D < TYPE >& vec, USMetaVec2D < TYPE >& p0, USMetaVec2D < TYPE >& p1 ) {

		u32 count = 0;
		USMetaVec2D < TYPE > sect [ 3 ];

		float tX;
		float tY;

		if (( vec.mX == 0 ) && ( vec.mY == 0 )) return false;

		if ( vec.mY == 0 ) {
		
			if ( loc.mY < this->mYMin ) return false;
			if ( loc.mY > this->mYMax ) return false;
			
			p0.Init ( this->mXMin, loc.mY );
			p1.Init ( this->mXMax, loc.mY );
			return true;
		}
		
		if ( vec.mX == 0 ) {
		
			if ( loc.mX < this->mXMin ) return false;
			if ( loc.mX > this->mXMax ) return false;
			
			p0.Init ( loc.mX, this->mYMin );
			p1.Init ( loc.mX, this->mYMax );
			return true;
		}

		TYPE r = vec.mY / vec.mX;

		// Check left
		tX = this->mXMin;
		tY = loc.mY + (( tX - loc.mX ) * r );
		if (( tY <= this->mYMax ) && ( tY >= this->mYMin )) {
			sect [ count++ ].Init ( tX, tY );
		}
		
		// Check right
		tX = this->mXMax;
		tY = loc.mY + (( tX - loc.mX ) * r );
		if (( tY <= this->mYMax ) && ( tY >= this->mYMin )) {
			sect [ count++ ].Init ( tX, tY );
		}

		if ( count < 2 ) {

			r = vec.mX / vec.mY;

			// Check top
			tY = this->mYMin;
			tX = loc.mX + (( tY - loc.mY ) * r );
			if (( tX <= this->mXMax ) && ( tX >= this->mXMin )) {
				sect [ count++ ].Init ( tX, tY );
			}
			
			// Check bottom
			tY = this->mYMax;
			tX = loc.mX + (( tY - loc.mY ) * r );
			if (( tX <= this->mXMax ) && ( tX >= this->mXMin )) {
				sect [ count++ ].Init ( tX, tY );
			}
		}
		
		if ( count < 2 ) return false;
		
		p0 = sect [ 0 ];
		p1 = sect [ 1 ];

		return true;
	}

	//----------------------------------------------------------------//
	USMetaVec2D < TYPE > GetNearestPoint ( const USMetaVec2D < TYPE >& point ) const {
	
		USMetaVec2D < TYPE > result;
		
		result.mX = USFloat::Clamp ( point.mX, this->mXMin, this->mXMax );
		result.mY = USFloat::Clamp ( point.mY, this->mYMin, this->mYMax );
		
		return result;
	}

	//----------------------------------------------------------------//
	void GetRect ( TYPE& left, TYPE& top, TYPE& right, TYPE& bottom ) const {

		left = this->mXMin;
		top = this->mYMin;
		right = this->mXMax;
		bottom = this->mYMax;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void Grow ( USMetaVec3D < PARAM_TYPE >& vec ) {

		if ( this->mXMin > ( TYPE )vec.mX ) this->mXMin = ( TYPE )vec.mX;
		else if ( this->mXMax < ( TYPE )vec.mX ) this->mXMax = ( TYPE )vec.mX;
	
		if ( this->mYMin > ( TYPE )vec.mY ) this->mYMin = ( TYPE )vec.mY;
		else if ( this->mYMax < ( TYPE )vec.mY ) this->mYMax = ( TYPE )vec.mY;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void Grow ( const USMetaVec2D < PARAM_TYPE >& point ) {

		if ( this->mXMin > ( TYPE )point.mX ) this->mXMin = ( TYPE )point.mX;
		else if ( this->mXMax < ( TYPE )point.mX ) this->mXMax = ( TYPE )point.mX;
	
		if ( this->mYMin > ( TYPE )point.mY ) this->mYMin = ( TYPE )point.mY;
		else if ( this->mYMax < ( TYPE )point.mY ) this->mYMax = ( TYPE )point.mY;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void Grow ( const USMetaRect < PARAM_TYPE >& rect ) {

		if ( this->mXMin > ( TYPE )rect.mXMin ) this->mXMin = ( TYPE )rect.mXMin;
		if ( this->mXMax < ( TYPE )rect.mXMax ) this->mXMax = ( TYPE )rect.mXMax;
	
		if ( this->mYMin > ( TYPE )rect.mYMin ) this->mYMin = ( TYPE )rect.mYMin;
		if ( this->mYMax < ( TYPE )rect.mYMax ) this->mYMax = ( TYPE )rect.mYMax;
	}

	//----------------------------------------------------------------//
	TYPE Height () const {
		TYPE height = this->mYMax - this->mYMin;
		return ( height < ( TYPE )0 ) ? -height : height;
	}

	//----------------------------------------------------------------//
	void Inflate ( TYPE size ) {

		this->mXMin -= size;
		this->mYMin -= size;
		this->mXMax += size;
		this->mYMax += size;
	}

	//----------------------------------------------------------------//
	template < typename PARAM_TYPE >
	void Init ( const USMetaVec2D < PARAM_TYPE >& point ) {

		this->mXMin = ( TYPE )point.mX;
		this->mXMax = ( TYPE )point.mX;

		this->mYMin = ( TYPE )point.mY;
		this->mYMax = ( TYPE )point.mY;
	}

	//----------------------------------------------------------------//
	void Init ( USMetaVec3D < TYPE >& vec ) {

		this->mXMin = vec.mX;
		this->mXMax = vec.mX;

		this->mYMin = vec.mY;
		this->mYMax = vec.mY;
	}

	//----------------------------------------------------------------//
	void Init ( TYPE left, TYPE top, TYPE right, TYPE bottom ) {

		this->mXMin = left;
		this->mXMax = right;

		this->mYMin = top;
		this->mYMax = bottom;
	}

	//----------------------------------------------------------------//
	bool Intersect ( const USMetaRect < TYPE >& rect, USMetaRect < TYPE >& result ) const {
		
		TYPE xMin = ( this->mXMin > rect.mXMin ) ? this->mXMin : rect.mXMin;
		TYPE xMax = ( this->mXMax < rect.mXMax ) ? this->mXMax : rect.mXMax;
		
		if ( xMin > xMax ) return false;
		
		TYPE yMin = ( this->mYMin > rect.mYMin ) ? this->mYMin : rect.mYMin;
		TYPE yMax = ( this->mYMax < rect.mYMax ) ? this->mYMax : rect.mYMax;
		
		if ( yMin > yMax ) return false;
		
		result.mXMin = xMin;
		result.mXMax = xMax;
		
		result.mYMin = yMin;
		result.mYMax = yMax;
		
		return true;
	}

	//----------------------------------------------------------------//
	void Offset ( TYPE xOff, TYPE yOff ) {
		
		this->mXMin += xOff;
		this->mXMax += xOff;
		
		this->mYMin += yOff;
		this->mYMax += yOff;
	}

	//----------------------------------------------------------------//
	bool Overlap ( const USMetaRect < TYPE >& rect ) const {
		
		if ( this->mXMin > rect.mXMax ) return false;
		if ( this->mXMax < rect.mXMin ) return false;
		
		if ( this->mYMin > rect.mYMax ) return false;
		if ( this->mYMax < rect.mYMin ) return false;
		
		return true;
	}
	
	//----------------------------------------------------------------//
	bool OverlapWithoutEdges ( const USMetaRect < TYPE >& rect ) const {
		
		if ( this->mXMin >= rect.mXMax ) return false;
		if ( this->mXMax <= rect.mXMin ) return false;
		
		if ( this->mYMin >= rect.mYMax ) return false;
		if ( this->mYMax <= rect.mYMin ) return false;
		
		return true;
	}

	//----------------------------------------------------------------//
	bool Overlap ( const USMetaVec2D < TYPE >& point, float radius ) const {
		
		USMetaVec2D < TYPE > nearest = this->GetNearestPoint ( point );
		
		return ( point.DistSqrd ( nearest ) <= ( radius * radius ));
	}

	//----------------------------------------------------------------//
	void Pad ( TYPE pad ) {

		this->mXMin -= pad;
		this->mYMin -= pad;
		
		this->mXMax += pad;
		this->mYMax += pad;
	}
	
	//----------------------------------------------------------------//
	void Scale ( float xScale, float yScale ) {
		
		this->mXMin *= xScale;
		this->mXMax *= xScale;
		
		this->mYMin *= yScale;
		this->mYMax *= yScale;
	}
	
	//----------------------------------------------------------------//
	void TransformLocalToWorld ( USMetaRect < TYPE >& rect ) const {
		
		float width = this->Width ();
		float height = this->Height ();
		
		rect.mXMin = ( TYPE )(( rect.mXMin * width ) + this->mXMin );
		rect.mYMin = ( TYPE )(( rect.mYMin * height ) + this->mYMin );
		
		rect.mXMax = ( TYPE )(( rect.mXMax * width ) + this->mXMin );
		rect.mYMax = ( TYPE )(( rect.mYMax * height ) + this->mYMin );
	}
	
	//----------------------------------------------------------------//
	void TransformWorldToLocal ( USMetaRect < TYPE >& rect ) const {
		
		float invWidth = 1.0f / this->Width ();
		float invHeight = 1.0f / this->Height ();
		
		rect.mXMin = ( TYPE )(( rect.mXMin - this->mXMin ) * invWidth );
		rect.mYMin = ( TYPE )(( rect.mYMin - this->mYMin ) * invHeight );
		
		rect.mXMax = ( TYPE )(( rect.mXMax - this->mXMin ) * invWidth );
		rect.mYMax = ( TYPE )(( rect.mYMax - this->mYMin ) * invHeight );
	}
	
	//----------------------------------------------------------------//
	TYPE Width () const {
		TYPE width = this->mXMax - this->mXMin;
		return ( width < ( TYPE )0 ) ? -width : width;
	}
};

typedef USMetaRect < float >	USRect;
typedef USMetaRect < double >	USDoubleRect;
typedef USMetaRect < int >		USIntRect;

#endif
