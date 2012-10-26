// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#import <moaiext-iphone/MOAIDialogIOS.h>
#import "GADRequest.h"

//================================================================//
// LuaAdView
//================================================================//
@implementation LuaAdView
  -(id)initWithFrame:(CGRect)frame {
		self = [super initWithFrame:CGRectMake(0.0,
                                            self.view.frame.size.height -
                                            GAD_SIZE_320x50.height,
                                            GAD_SIZE_320x50.width,
                                            GAD_SIZE_320x50.height)];
		if (self) {
			self.delegate = self;
		}
		return self;
  }
	
	
	// ----------------------------------------
	- (void)adViewDidReceiveAd:(GADBannerView *)view  {
		
	}

	- (void)adView:(GADBannerView *)view
	    didFailToReceiveAdWithError:(GADRequestError *)error{
	    	
	    }
	
@end

//================================================================//
// lua
//================================================================//

int MOAIAdMobIOS::_showBanner (lua_State* L) {
	MOAILuaState state ( L );
	
	cc8* appID = state.GetValue < cc8* >(1, "");

  UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
  UIViewController* rootVC = [ window rootViewController ];  
  
  LuaAdView *v = [[LuaAdView alloc] initWithFrame:CGRectZero];
  v.adUnitID = appID;
  v.rootViewController = rootVC;
  [rootVC.view addSubview:v];
  [v loadRequest:[GADRequest request]];
}

//================================================================//
// MOAIDialogIOS
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
