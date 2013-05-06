#ifndef MOAIKAKAOLINK_H
#define MOAIKAKAOLINK_H

#ifndef DISABLE_KAKAO

#include <moaicore/moaicore.h>

//================================================================//
// MOAIKakaoLink
//================================================================//
class MOAIKakaoLink :
  public MOAIGlobalClass < MOAIKakaoLink, MOAILuaObject > {
private:

  //----------------------------------------------------------------//
  static int  _openKakaoLink ( lua_State* L ); 

public:
  
  DECL_LUA_SINGLETON ( MOAIKakaoLink ); 
  
      MOAIKakaoLink   ();
      ~MOAIKakaoLink    ();

  void  RegisterLuaClass    ( MOAILuaState& state ); 
};

#endif
#endif