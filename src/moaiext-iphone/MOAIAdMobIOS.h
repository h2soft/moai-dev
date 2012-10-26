// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIDIALOGIOS_H
#define	MOAIDIALOGIOS_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <moaicore/moaicore.h>
#import "GADBannerView.h"

//================================================================//
// MOAIAdMobIOS
//================================================================//
/**	@name	MOAIAdMobIOS
	@text	Wrapper for a simple native dialog implementation on 
			iOS devices. Exposed to lua via MOAIDialog on all 
			mobile platforms.

	@const	DIALOG_RESULT_POSITIVE	Result code when the dialog is dismissed by pressing the positive button.
	@const	DIALOG_RESULT_NEUTRAL	Result code when the dialog is dismissed by pressing the neutral button.
	@const	DIALOG_RESULT_NEGATIVE	Result code when the dialog is dismissed by pressing the negative button.
	@const	DIALOG_RESULT_CANCEL	Result code when the dialog is dismissed by pressing the cancel button.
*/
class MOAIAdMobIOS :
	public MOAIGlobalClass < MOAIAdMobIOS, MOAILuaObject > {
private:

	//----------------------------------------------------------------//
	static int	_showBanner	( lua_State* L );

public:
	
	DECL_LUA_SINGLETON ( MOAIAdMobIOS )
	
			MOAIAdMobIOS		();
			~MOAIAdMobIOS		();
	void	RegisterLuaClass	( MOAILuaState& state );
};

@interface LuaAdView : GADBannerView {
@public

	MOAILuaRef 	callback;
};

- (id)initWithFrame:(CGRect)frame;

@end

#endif
