// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#import <moaiext-iphone/MOAIAdMobIOS.h>
#import <moaiext-iphone/NSString+MOAILib.h>


//================================================================//
// LuaAdView
//================================================================//
@implementation LuaAdView

- ( id ) initWithAdSize:( NSString* ) appID viewController:(UIViewController* )rootVC {

  bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
  bannerView.adUnitID = appID;
  bannerView.rootViewController = rootVC;

  [bannerView loadRequest:[GADRequest request]];
}
	
	// ----------------------------------------
//	- (void)adViewDidReceiveAd:(GADBannerView *)view  {
//		
//	}
//
//	- (void)adView:(GADBannerView *)view
//	    didFailToReceiveAdWithError:(GADRequestError *)error{
//	    	
//	    }

@end

//================================================================//
// lua
//================================================================//

int MOAIAdMobIOS::_showBanner (lua_State* L) {

	MOAILuaState state ( L );
	
	cc8* appID = state.GetValue < cc8* >(1, "");
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	//UIViewController* rootVC = [ window rootViewController ];  
  
  LuaAdView* adView = [[ LuaAdView alloc] initWithAdSize:[NSString stringWithUTF8String:appID]
      viewController:[UIViewController];

/**
  bannerView.adUnitID = appIdStr;
  bannerView.rootViewController = rootVC
  [rootVC.view addSubview:bannerView];

  [bannerView loadRequest:[GADRequest request]];
*/
/**
	LuaAdView *v = [[LuaAdView alloc] initWithFrame:CGRectMake(0.0, rootVC.view.frame.size.height - 50, 320, 50)];
	
	v.adUnitID = appIdStr;
	v.rootViewController = rootVC;
	[rootVC.view addSubview:v];
	[v loadRequest:[GADRequest request]];
*/
//
  return 0;
}

//================================================================//
// MOAIAdMobIOS
//================================================================//

//----------------------------------------------------------------//
MOAIAdMobIOS::MOAIAdMobIOS () {

	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIAdMobIOS::~MOAIAdMobIOS () {
}

//----------------------------------------------------------------//
void MOAIAdMobIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "showBanner",	_showBanner },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
