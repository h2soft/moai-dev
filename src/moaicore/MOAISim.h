// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAISIM_H
#define	MOAISIM_H

#include <moaicore/MOAIEaseDriver.h>

class MOAIProp2D;

//================================================================//
// MOAISim
//================================================================//
/**	@brief Sim information and settings class.
*/
class MOAISim :
	public USGlobalClass < MOAISim, USLuaObject > {
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

	typedef USList < MOAIProp2D* >::Iterator RenderPassIt;
	USList < MOAIProp2D* > mRenderPasses;
	
	USCallback < int > mLoadingScreenCallback;
	USCallback < int > mTextInputCallback;
	
	bool			mNeedsInit;
	STLString		mInitFromFilename;
	STLString		mInitFromString;
	
	GLbitfield		mClearFlags;
	u32				mClearColor;
	
	STLString		mUniqueID;
	
	bool			mHasNetwork;
	
	USTaskThread	mDataIOThread;
	
	//----------------------------------------------------------------//
	static int		_clearRenderStack			( lua_State* L );
	static int		_enterFullscreenMode		( lua_State* L );
	static int		_exitFullscreenMode			( lua_State* L );
	static int		_framesToTime				( lua_State* L );
	static int		_getDeviceIDString			( lua_State* L );
	static int		_getDeviceSize				( lua_State* L );
	static int		_getElapsedFrames			( lua_State* L );
	static int		_getElapsedTime				( lua_State* L );
	static int		_getFrameSize				( lua_State* L );
	static int		_getNetworkStatus			( lua_State* L );
	static int		_openWindow					( lua_State* L );
	static int		_pauseTimer					( lua_State* L );
	static int		_popRenderPass				( lua_State* L );
	static int		_pushRenderPass				( lua_State* L );
	static int		_setClearColor				( lua_State* L );
	static int		_setClearDepth				( lua_State* L );
	static int		_setFrameSize				( lua_State* L );
	static int		_timeToFrames				( lua_State* L );

	//----------------------------------------------------------------//

public:
	
	
	DECL_LUA_SINGLETON ( MOAISim )
	
	GET ( USTaskThread&, DataIOThread, mDataIOThread )
	
	//----------------------------------------------------------------//
	void		Clear						();
				MOAISim						();
				~MOAISim					();
	void		PauseMOAI					();
	void		PopRenderPass				();
	void		PushRenderPass				( MOAIProp2D* prop );
	void		RegisterLuaClass			( USLuaState& state );
	void		Render						();
	void		ResumeMOAI					();
	void		RunFile						( cc8* filename );
	void		RunString					( cc8* script );
	void		SetHeading					( double degrees );
	void		SetLonLat					( double lon, double lat, double accuracy );
	void		SetReachability				( bool networkStatus );
	void		SetUniqueIdentifier			( cc8* uniqueID );
	void		Update						();
	STLString	ToString					();
};

#endif
