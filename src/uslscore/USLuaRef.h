// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef LUAREF_H
#define LUAREF_H

#include <uslscore/USLeanArray.h>

class USLuaRuntime;
class USLuaState;
class USLuaStateHandle;

//================================================================//
// USLuaRefTable
//================================================================//
class USLuaRefTable {
private:

	friend class USLuaRef;

	int		mTableID;
	
	static const u32		MAX_REF_ID = 0xffffffff;

	static const u32		REFID_CHUNK_SIZE = 1024;
	USLeanArray < u32 >		mRefIDStack;
	u32						mRefIDStackTop;

	//----------------------------------------------------------------//
	void		ReleaseRefID		( int refID );
	int			ReserveRefID		();

public:

	//----------------------------------------------------------------//
	void		Clear				();
	void		InitStrong			();
	void		InitWeak			();
	void		PushRef				( USLuaState& state, int refID );
	int			Ref					( USLuaState& state, int idx );
	void		Unref				( USLuaState& state, int refID );
				USLuaRefTable		();
				~USLuaRefTable		();
};

//================================================================//
// USLuaRef
//================================================================//
class USLuaRef {
private:

	int			mRef;
	bool		mOwnsRef;
	bool		mWeak;

	//----------------------------------------------------------------//
	void					SetRef			( USLuaState& state, int idx, bool weak );

public:

	static const bool STRONG_REF	= false;
	static const bool WEAK_REF		= true;

	//----------------------------------------------------------------//
	void					Clear			();
	bool					IsNil			();
	bool					IsWeak			();
	u32						GetID			();
	USLuaStateHandle		GetSelf			();
	void					MakeStrong		();
	void					MakeWeak		();
	bool					PushRef			( USLuaState& state );
	void					SetStrongRef	( USLuaState& state, int idx );
	void					SetWeakRef		( USLuaState& state, int idx );
	void					Take			( const USLuaRef& assign );
							USLuaRef		();
							USLuaRef		( const USLuaRef& assign );
							~USLuaRef		();
	void					WeakCopy		( const USLuaRef& assign );

	//----------------------------------------------------------------//
	inline void operator = ( const USLuaRef& assign ) {
		this->Take ( assign );
	}

	//----------------------------------------------------------------//
	inline bool operator < ( const USLuaRef& compare ) const {
	
		if ( this->mWeak != compare.mWeak ) {
			return this->mWeak;
		}
		return ( this->mRef < compare.mRef );
	}

	//----------------------------------------------------------------//
	inline operator bool () {
		return ( this->mRef != LUA_NOREF );
	}
};

#endif
