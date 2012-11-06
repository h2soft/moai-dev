// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIADMOBIOS_H
#define	MOAIADMOBIOS_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <moaicore/moaicore.h>

#import "GADBannerView.h"
#import "GADBannerViewDelegate.h"

//================================================================//
// MOAIAdMobIOS
//================================================================//

class MOAIAdMobIOS :
public MOAIGlobalClass < MOAIAdMobIOS, MOAILuaObject > {
private:

  GADBannerView *bannerView;
	static int _showBanner	( lua_State* L );
  static int _dismiss( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIAdMobIOS )
	
			MOAIAdMobIOS		();
			~MOAIAdMobIOS		();
	void	RegisterLuaClass	( MOAILuaState& state );
};

#endif
