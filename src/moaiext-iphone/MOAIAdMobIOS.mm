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
	cc8* align = state.GetValue < cc8* >(2, "Top");
	bool testing = state.GetValue < bool > (3, false);
	
	NSString* alignment = [NSString stringWithUTF8String:align];
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];

	int x = rootVC.view.frame.size.height/2;
	int y = 0;

	if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
		x = x - 728/2;
		if ([alignment isEqualToString:@"Center"]) {
			y = rootVC.view.frame.size.width/2 - 90/2;
		}
		else if ([alignment isEqualToString:@"Bottom"]) {
			y = rootVC.view.frame.size.width - 90;
		}
		CGPoint origin = CGPointMake((float)x, (float)y);
		MOAIAdMobIOS::Get().bannerView = [[[GADBannerView alloc] initWithAdSize:kGADAdSizeLeaderboard origin:origin] autorelease]; // 728 * 90
	}
	else {
		x = x - 320/2;
		if ([alignment isEqualToString:@"Center"]) {
			y = rootVC.view.frame.size.width/2 - 50/2;
		}
		else if ([alignment isEqualToString:@"Bottom"]) {
			y = rootVC.view.frame.size.width - 50;
		}
		CGPoint origin = CGPointMake((float)x, (float)y);
		MOAIAdMobIOS::Get().bannerView = [[[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:origin] autorelease];	//320 * 50
	}



  // Note: Edit SampleConstants.h to provide a definition for kSampleAdUnitID
  // before compiling.
  MOAIAdMobIOS::Get().bannerView.adUnitID = [NSString stringWithUTF8String:appID];
  //MOAIAdMobIOS::Get().bannerView.delegate = self;
  [MOAIAdMobIOS::Get().bannerView setRootViewController:rootVC];
  [rootVC.view addSubview:MOAIAdMobIOS::Get().bannerView];

  GADRequest *request = [GADRequest request];
	request.testing = testing;

  [MOAIAdMobIOS::Get().bannerView loadRequest:request];

  //view 재사용 구현 or 지우고 다시 만들기.
  //콜 백 구현
  return 0;
}

int MOAIAdMobIOS::_dismiss(lua_State* L) {
	[MOAIAdMobIOS::Get().bannerView removeFromSuperview];
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
