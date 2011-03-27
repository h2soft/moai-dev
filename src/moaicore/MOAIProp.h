// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPROP_H
#define	MOAIPROP_H

#include <moaicore/MOAITransform.h>

class MOAIPartition;
class MOAIPartitionCell;
class MOAIPartitionLayer;

class MOAISurfaceSampler2D;

//================================================================//
// MOAIProp
//================================================================//
class MOAIProp :
	public MOAITransform {
private:

	friend class MOAIPartition;
	friend class MOAIPartitionCell;
	friend class MOAIPartitionLayer;

	MOAIPartition*				mPartition;	
	MOAIPartitionLayer*			mLayer;
	MOAIPartitionCell*			mCell;
	
	USLeanLink < MOAIProp* >	mLinkInCell;
	MOAIProp*					mNextResult;

	u32				mMask;
	USRect			mBounds;
	float			mCellSize;
	s32				mPriority;
	
	//----------------------------------------------------------------//
	static int		_getPriority		( lua_State* L );
	static int		_setPriority		( lua_State* L );

	//----------------------------------------------------------------//
	void			SetBounds			();
	void			SetBounds			( const USRect& bounds );

public:

	static const s32 UNKNOWN_PRIORITY = 0x80000000;

	enum {
		BOUNDS_EMPTY,
		BOUNDS_GLOBAL,
		BOUNDS_OK,
	};

	GET_SET ( u32, Mask, mMask )
	GET ( s32, Priority, mPriority )

	//----------------------------------------------------------------//
	virtual void	Draw				();
	virtual void	DrawDebug			();
	virtual void	GatherSurfaces		( MOAISurfaceSampler2D& sampler );
	USRect			GetBounds			();
	bool			GetCellRect			( USRect* cellRect, USRect* paddedRect = 0 );
					MOAIProp			();
	virtual			~MOAIProp			();
	void			RegisterLuaClass	( USLuaState& state );
	void			RegisterLuaFuncs	( USLuaState& state );
	void			UpdateBounds		( u32 status );
	void			UpdateBounds		( const USRect& bounds, u32 status );
};

#endif
