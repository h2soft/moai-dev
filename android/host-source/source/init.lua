--==============================================================-- Copyright (c) 2010-2011 Zipline Games, Inc. -- All Rights Reserved. -- http://getmoai.com--==============================================================	package.path = "?;?.lua"		----------------------------------------------------------------	-- this function supports all the ways a user could call print	----------------------------------------------------------------	print = function ( ... )				local argCount = #arg				if argCount == 0 then			MOAILogMgr.log ( "" )			return		end				local output = tostring ( arg [ 1 ])				for i = 2, argCount do			output = output .. "\t" .. tostring ( arg [ i ])		end				MOAILogMgr.log ( output )	end