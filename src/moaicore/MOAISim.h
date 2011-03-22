// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAISIM_H
#define	MOAISIM_H

#include <moaicore/MOAIForceAction.h>

class MOAIPrim;

//================================================================//
// MOAISim
//================================================================//
/**	@brief Sim information and settings class.
*/
class MOAISim :
	public USGlobalClass < MOAISim, USLuaData > {
private:

	// timer state
	enum {
		RUNNING,
		PAUSED,
		RESUMING,
	};

	u32				mTimerState;

	double			mDeviceTime; // elapsed device time since last update
	double			mStep; // simulation step size
	double			mTime; // elapsed simulation running time (in steps)
	
	USLuaRef		mOnTextEntry;
	USLuaRef		mOnCancelTextEntry;

	typedef USList < MOAIPrim* >::Iterator RenderPassIt;
	USList < MOAIPrim* > mRenderPasses;
	
	USCallback < int > mLoadingScreenCallback;
	USCallback < int > mTextInputCallback;
	
	bool			mNeedsInit;
	STLString		mInitFromFilename;
	STLString		mInitFromString;
	
	GLbitfield		mClearFlags;
	u32				mClearColor;
	
	STLString		mPrefsPath;
	STLString		mUniqueID;
	
	bool			mHasNetwork;
	
	USTaskThread	mDataIOThread;
	
	//----------------------------------------------------------------//
	static int		_clearRenderStack			( lua_State* L );
	static int		_enterFullscreenMode		( lua_State* L );
	static int		_exitFullscreenMode			( lua_State* L );
	static int		_framesToTime				( lua_State* L );
	static int		_getDeviceIDString			( lua_State* L );
	static int		_getElapsedFrames			( lua_State* L );
	static int		_getElapsedTime				( lua_State* L );
	static int		_getFrameSize				( lua_State* L );
	static int		_getNetworkStatus			( lua_State* L );
	static int		_getUserInput				( lua_State* L );
	static int		_getUserPrefs				( lua_State* L );
	static int		_openWindow					( lua_State* L );
	static int		_pauseTimer					( lua_State* L );
	static int		_popRenderPass				( lua_State* L );
	static int		_pushRenderPass				( lua_State* L );
	static int		_serializeToString			( lua_State* L );
	static int		_setClearColor				( lua_State* L );
	static int		_setClearDepth				( lua_State* L );
	static int		_setFrameSize				( lua_State* L );
	static int		_setLoading					( lua_State* L );
	static int		_setTextInputCallback		( lua_State* L );
	static int		_setTextInputCancelCallback	( lua_State* L );
	static int		_setUserPrefs				( lua_State* L );
	static int		_setVirtualSize				( lua_State* L );
	static int		_timeToFrames				( lua_State* L );

	//----------------------------------------------------------------//
	bool			SetLoadingScreenStatus		( bool showLoadingScreen );
	bool			ShowTextPrompt				( int keyboardType );

public:
	
	enum {
		KEYBOARD_TYPE_DEFAULT,
		KEYBOARD_TYPE_ASCII_CAPABLE,
		KEYBOARD_TYPE_NUMBERS_AND_PUNC,
		KEYBOARD_TYPE_URL,
		KEYBOARD_TYPE_NUMBER_PAD,
		KEYBOARD_TYPE_PHONE_PAD,
		KEYBOARD_TYPE_NAME_PHONE_PAD,
		KEYBOARD_TYPE_EMAIL_ADDR,
		KEYBOARD_TYPE_ALPHABET = KEYBOARD_TYPE_ASCII_CAPABLE,
	};
	
	DECL_LUA_SINGLETON ( MOAISim )
	
	GET ( USCallback < int >&, LoadingScreenCallback, mLoadingScreenCallback )
	GET ( USCallback < int >&, TextInputCallback, mTextInputCallback )
	GET ( USTaskThread&, DataIOThread, mDataIOThread )
	
	//----------------------------------------------------------------//
	void		Clear						();
				MOAISim						();
				~MOAISim					();
	void		OnTextInputCallback			( cc8* text );
	void		OnTextInputCancelCallback	();
	void		PauseMOAI					();
	void		PopRenderPass				();
	void		PushRenderPass				( MOAIPrim* prim );
	void		RegisterLuaClass			( USLuaState& state );
	void		Render						();
	void		ResumeMOAI					();
	void		RunFile						( cc8* filename );
	void		RunString					( cc8* script );
	void		SetHeading					( double degrees );
	void		SetLonLat					( double lon, double lat, double accuracy );
	void		SetPrefsPath				( cc8* path );
	void		SetReachability				( bool networkStatus );
	void		SetUniqueIdentifier			( cc8* uniqueID );
	void		Update						();
	STLString	ToString					();
};

#endif
