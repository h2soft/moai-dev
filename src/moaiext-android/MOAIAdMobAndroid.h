//----------------------------------------------------------------//
// Copyright (c) 2012 H2SOFT Co., Ltd
// All Rights Reserved. 
// http://www.h2soft.kr
//----------------------------------------------------------------//

#ifndef MOAIADMOBANDROID_H
#define MOAIADMOBANDROID_H

#ifndef DISABLE_ADMOB

#include <moaicore/moaicore.h>

//================================================================//
// MOAIAdMobAndroid
//================================================================//
/**	@name	MOAIAdMobAndroid
 @text	Wrapper for AdMob integration on Android devices.
 Exposed to lua via MOAIAdMob on 
 all mobile platforms.
 
 */
class MOAIAdMobAndroid :
public MOAIGlobalClass < MOAIAdMobAndroid, MOAILuaObject > {
private:
	
	//----------------------------------------------------------------//
	static int _showBanner		( lua_State* L );
	static int _dismiss			( lua_State* L );
	
	static cc8*	_luaParseTable 		( lua_State * L, int idx );
	static jobject _luaReadMap		( lua_State * L, int idx );

public:
    
	DECL_LUA_SINGLETON ( MOAIAdMobAndroid );
	
	MOAIAdMobAndroid		();
	~MOAIAdMobAndroid		();
	void	RegisterLuaClass	( MOAILuaState& state );
};

#endif  //DISABLE_ADMOB

#endif // MOAIADMOB_H
