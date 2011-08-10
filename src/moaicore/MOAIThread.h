// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAITHREAD_H
#define	MOAITHREAD_H

#include <moaicore/MOAIAction.h>

//================================================================//
// MOAIThread
//================================================================//
/**	@name MOAIThread
	@text Binds a Lua coroutine to a MOAIAction.
*/
class MOAIThread :
	public MOAIAction {
private:

	USLuaRef		mRef;
	lua_State*		mState;
	u32				mNarg;
	STLString		mFuncName;
	
	//----------------------------------------------------------------//
	static int		_blockOnAction			( lua_State* L );
	static int		_currentThread			( lua_State* L );
	static int		_run					( lua_State* L );
	
	//----------------------------------------------------------------//
	
public:
	
	DECL_LUA_FACTORY ( MOAIThread )
	
	//----------------------------------------------------------------//						
					MOAIThread				();
					~MOAIThread				();
	bool			IsDone					();
	void			OnUpdate				( float step );
	void			RegisterLuaClass		( USLuaState& state );
	void			RegisterLuaFuncs		( USLuaState& state );

	STLString		ToString				();
};

#endif
