----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "moai.png" )
gfxQuad:setRect ( -64, -64, 64, 64 )

prop = MOAIProp2D.new ()
prop:setDeck ( gfxQuad )
layer:insertProp ( prop )

prop:moveRot ( 360, 3.0 )

MOAITstoreBilling.setListener(MOAITstoreBilling.PURCHASE_COMPLETE, function() 
	print("PURCHASE_COMPLETE")
	end)
MOAITstoreBilling.setListener(MOAITstoreBilling.PURCHASE_CANCEL, function() 
	print("PURCHASE_CANCEL")
	end)
MOAITstoreBilling.setListener(MOAITstoreBilling.PURCHASE_ERROR, function(errorCode, subCode) 
	print("PURCHASE_ERROR", errorCode, subCode)
	end)
MOAITstoreBilling.setApplicationId("OA00304511")
MOAITstoreBilling.requestPurchase("0900626310")

