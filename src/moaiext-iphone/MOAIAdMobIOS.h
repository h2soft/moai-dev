// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIADMOBIOS_H
#define	MOAIADMOBIOS_H

#ifndef DISABLE_ADMOB

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <moaicore/moaicore.h>

#import "GADRequest.h"
#import "GADRequestError.h"
#import "GADBannerView.h"
#import "GADAdSize.h"
#import "GADAdMobExtras.h"
#import "GADAdNetworkExtras.h"
#import "GADBannerViewDelegate.h"
#import "GADInterstitial.h"
#import "GADInterstitialDelegate.h"


//================================================================//
// MOAIAdMobIOS
//================================================================//

class MOAIAdMobIOS :
public MOAIGlobalClass < MOAIAdMobIOS, MOAILuaObject > {
private:

	static int	_showBanner	( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIAdMobIOS )
	
			MOAIAdMobIOS		();
			~MOAIAdMobIOS		();
	void	RegisterLuaClass	( MOAILuaState& state );
};

@interface LuaAdView : GADBannerView {
@public
};

@end

#endif

#endif
