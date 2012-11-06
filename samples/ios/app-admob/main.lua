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

MOAIAdMobIOS.showBanner("a150850c90d5b6c")
MOAIAdMobIOS.showBanner("a150850c90d5b6c", "Center")
MOAIAdMobIOS.showBanner("a150850c90d5b6c", "Bottom")

--[[
timer = MOAITimer.new()
timer:setSpan(10)
timer:setMode(MOAITimer.NORMAL)
timer:setListener(MOAITimer.NORMAL, function()
  MOAIAdMobIOS.dismiss()
end)
timer:start()
]]
