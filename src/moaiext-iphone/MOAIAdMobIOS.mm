//----------------------------------------------------------------//
// Copyright (c) 2012 H2SOFT Co., Ltd
// All Rights Reserved. 
// http://www.h2soft.kr
//----------------------------------------------------------------//

#include "pch.h"
#import <moaiext-iphone/MOAIAdMobIOS.h>
#import <moaiext-iphone/NSString+MOAILib.h>

#import "GADAdSize.h"
#import "GADRequest.h"

//================================================================//
// lua
//================================================================//


int MOAIAdMobIOS::_showBanner (lua_State* L) {

	MOAILuaState state ( L );
	
	cc8* appID = state.GetValue < cc8* >(1, "");
	bool testing = state.GetValue < bool > (2, false);
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];
	
	GADAdSize bannerSize = UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad ? kGADAdSizeLeaderboard : kGADAdSizeBanner;
	GADBannerView* bannerView = [[ GADBannerView alloc ] initWithAdSize:bannerSize ];
	
	CGRect frame = rootVC.view.bounds;
	bannerView.center = CGPointMake ( frame.size.width/2, frame.size.height - bannerView.bounds.size.height/2 );
	bannerView.adUnitID = [ NSString stringWithUTF8String:appID ];
	//bannerView.delegate = self;
	[ bannerView setRootViewController:rootVC ];
	[ rootVC.view addSubview:bannerView ];
	 
	GADRequest *request = [ GADRequest request ];
	request.testing = testing; 
	[ bannerView loadRequest:request ];
	
	MOAIAdMobIOS::Get().bannerView = bannerView;
	[ bannerView release ];

  return 0;
}

int MOAIAdMobIOS::_dismiss(lua_State* L) {
	[ MOAIAdMobIOS::Get().bannerView removeFromSuperview ];
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
		{ "dismiss",	_dismiss },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
