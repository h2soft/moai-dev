// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <uslscore/uslscore.h>
#include <physfs.h>

//----------------------------------------------------------------//
static void _cleanup () {

	PHYSFS_deinit ();

	USGlobals::Get ()->Finalize ();
}

//----------------------------------------------------------------//
// TODO: this should be part of the unit tests
static void _typeCheck () {

	// make sure our fixed size typedefs are what we think
	// they are on the current platform/compiler
	assert ( sizeof ( cc8 )	== 1 );

	assert ( sizeof ( u8 )	== 1 );
	assert ( sizeof ( u16 )	== 2 );
	assert ( sizeof ( u32 )	== 4 );
	assert ( sizeof ( u64 )	== 8 );
	
	assert ( sizeof ( s8 )	== 1 );
	assert ( sizeof ( s16 )	== 2 );
	assert ( sizeof ( s32 )	== 4 );
	assert ( sizeof ( s64 )	== 8 );
}

//================================================================//
// uslscore
//================================================================//

//----------------------------------------------------------------//
void uslscore::InitGlobals ( USGlobals* globals ) {

	static bool sysInit = true;
	if ( sysInit ) {;

		_typeCheck ();

		//#ifdef _WIN32
		//	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF );
		//#endif
		
		srand (( u32 )time ( 0 ));
		atexit ( _cleanup );

		// get current path for PhysFS init		
		char path [ PATH_MAX ];
		char* str = getcwd ( path, PATH_MAX );
		UNUSED ( str );

		// init PhysFS
		PHYSFS_init ( "MOAI" );
		PHYSFS_addToSearchPath ( path, 1 ); //init search path to current working dir
		PHYSFS_setWriteDir ( path );        //init write directory to current working dir
		
		sysInit = false;
	}

	USGlobals::Get ()->Set ( globals );

	USLuaRuntime::Get ();
}
