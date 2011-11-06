// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIHTTPTASK_H
#define	MOAIHTTPTASK_H

#include <moaicore/MOAILua.h>

class USHttpTask;
class MOAIDataBuffer;

//================================================================//
// MOAIHttpTask
//================================================================//
/**	@name	MOAIHttpTask
	@text	Object for performing asynchronous http actions.
*/
class MOAIHttpTask :
	public virtual MOAIObject {
private:

	void*				mBuffer;
	u32					mSize;

	MOAILuaLocal		mOnFinish;
	
	MOAILuaSharedPtr < MOAIDataBuffer > mPostData;
	STLString mPostString;

	//----------------------------------------------------------------//
	static int		_getSize			( lua_State* L );
	static int		_getString			( lua_State* L );
	static int		_httpGet			( lua_State* L );
	static int		_httpPost			( lua_State* L );
	static int		_parseXml			( lua_State* L );
	static int		_setCallback		( lua_State* L );
	
	//----------------------------------------------------------------//
	void			OnHttpFinish	( USHttpTask* fetcher );
	
public:
	
	GET ( void*, Buffer, mBuffer )
	GET ( u32, Size, mSize )
	
	DECL_LUA_FACTORY ( MOAIHttpTask )
	
	//----------------------------------------------------------------//
	void			Clear					();						
					MOAIHttpTask			();
					~MOAIHttpTask			();
	void			Init					( u32 size );
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
