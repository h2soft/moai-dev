#include "pch.h"
#import <moaiext-iphone/MOAIAdMobIOS.h>
#import <moaiext-iphone/NSString+MOAILib.h>

//#import "GADAdSize.h"
#import "GADRequest.h"

//================================================================//
// lua
//================================================================//


int MOAIAdMobIOS::_showBanner (lua_State* L) {

	MOAILuaState state ( L );
	
	cc8* appID = state.GetValue < cc8* >(1, "");
	
	UIWindow* window = [[ UIApplication sharedApplication ] keyWindow ];
	UIViewController* rootVC = [ window rootViewController ];  

  //매번 뷰를 생성해서 컨트롤러에 붙인다.
  // CGPoint origin = CGPointMake(0.0,
                                // rootVC.view.frame.size.height -
                                // CGSizeFromGADAdSize(kGADAdSizeBanner).height);
 
  MOAIAdMobIOS::Get().bannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
                                                 // origin:origin];

  // Note: Edit SampleConstants.h to provide a definition for kSampleAdUnitID
  // before compiling.
  MOAIAdMobIOS::Get().bannerView.adUnitID = [NSString stringWithUTF8String:appID];
  //MOAIAdMobIOS::Get().bannerView.delegate = self;
  [MOAIAdMobIOS::Get().bannerView setRootViewController:rootVC];
  [rootVC.view addSubview:MOAIAdMobIOS::Get().bannerView];

  GADRequest *request = [GADRequest request];
  request.testing = YES;

  [MOAIAdMobIOS::Get().bannerView loadRequest:request];

  //dismiss 구현
  //view 재사용 구현 or 지우고 다시 만들기.

  //콜 백 구현

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
