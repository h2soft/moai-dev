print ( "hello, moai!" )

scene = MOAILayer2D.new ()

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

scene:setViewport ( viewport )
MOAISim.pushRenderPass ( scene )

----------------------------------------------------------------
-- set us up the ninepatch
ninePatch = MOAIStretchPatch.new ()
ninePatch:setTexture ( "cathead.png" )

ninePatch:reserveRows ( 3 )
ninePatch:setRow ( 0, 0.25, false )
ninePatch:setRow ( 1, 0.50, true )
ninePatch:setRow ( 2, 0.25, false )

ninePatch:reserveColumns ( 3 )
ninePatch:setColumn ( 0, 0.25, false )
ninePatch:setColumn ( 1, 0.50, true )
ninePatch:setColumn ( 2, 0.25, false )

ninePatch:reserveUVRects ( 3 )
ninePatch:setUVRect ( 0, 0, 0.5, 0.5, 0 )
ninePatch:setUVRect ( 1, 0.5, 1, 1, 0.5 )
ninePatch:setUVRect ( 2, 0, 1, 1, 0 )

ninePatch:setRect ( -64, -64, 64, 64 )

sprite = MOAIProp2D.new ()
sprite:setDeck ( ninePatch )
sprite:setFrame ( -128, -128, 128, 128 )
sprite:setFrameSource ( MOAIProp2D.FRAME_FROM_DEFINE )
sprite:setIndex ( 2 )
scene:insertPrim ( sprite )

----------------------------------------------------------------
MOAISim.openWindow ( "ninepatch", 320, 480 )

