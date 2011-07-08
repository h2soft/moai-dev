--==============================================================
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
--==============================================================

require "tapjoy"

SCREEN_UNITS_X = 640
SCREEN_UNITS_Y = 960

if MOAIEnvironment.isRetinaDisplay () then
	SCREEN_WIDTH = 320
	SCREEN_HEIGHT = 480
else
	SCREEN_WIDTH = 640
	SCREEN_HEIGHT = 960
end

viewport = MOAIViewport.new ()
viewport:setSize ( SCREEN_WIDTH, SCREEN_HEIGHT )
viewport:setScale ( SCREEN_UNITS_X, SCREEN_UNITS_Y )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

--==============================================================
-- tapjoy examples
--==============================================================

--ACTIVE_EXAMPLE = "showOffersWebView"
--ACTIVE_EXAMPLE = "showFeaturedAppWebView"
ACTIVE_EXAMPLE = "getBannerAdProp"

tapjoy.init ( "7f0cc735-d561-4761-b74b-91fd6787d200", "ZnIBakPig9ygaJN4lAod" )

-----------------------------------------------------------------
-- offers webview example
-----------------------------------------------------------------
if ACTIVE_EXAMPLE == "showOffersWebView" then
	
	function showOffersWebViewCallback ( task, webView )

		webView:show ()
	end

	tapjoy.showOffersWebView ( showOffersWebViewCallback )
end

-----------------------------------------------------------------
-- featured app ad example
-----------------------------------------------------------------
if ACTIVE_EXAMPLE == "showFeaturedAppWebView" then

	function showFeaturedAppWebViewCallback ( task, webView )

		webView:show ()
	end

	tapjoy.showFeaturedAppWebView ( showFeaturedAppWebViewCallback )
end

-----------------------------------------------------------------
-- banner ad example
-----------------------------------------------------------------
if ACTIVE_EXAMPLE == "getBannerAdProp" then

	function getBannerAdPropCallback ( task, bannerProp )

		-- add banner ad prop to layer
		layer:insertProp ( bannerProp )
		
		-- set up click behavior for banner ad prop
		MOAIInputMgr.device.touch:setCallback ( 
			
			function ( eventType, id, x, y, tapCount )
			
				if ( eventType == MOAITouchSensor.TOUCH_DOWN ) and bannerProp:inside ( layer:wndToWorld ( x, y )) then
					local jsonTable = MOAIJsonParser.decode ( task:getString () )
					MOAIWebView.openUrlInSafari ( jsonTable.ClickURL )
				end
			end
		)
	end

	tapjoy.getBannerAdProp ( "640x100", getBannerAdPropCallback )
end
