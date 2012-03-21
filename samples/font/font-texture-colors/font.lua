--MOAI
serializer = ... or MOAIDeserializer.new ()

local function init ( objects )

	--Initializing Tables
	local table

	table = objects [ 0x021B4380 ]

	--MOAIFont
	serializer:initObject (
		objects [ 0x021D3F9C ],
		objects [ 0x021B4380 ],
		{
			[ "mByteGlyphMap" ] = {
				[ 1 ]	= 62,
				[ 2 ]	= 67,
				[ 3 ]	= 255,
				[ 4 ]	= 255,
				[ 5 ]	= 255,
				[ 6 ]	= 255,
				[ 7 ]	= 71,
				[ 8 ]	= 255,
				[ 9 ]	= 69,
				[ 10 ]	= 70,
				[ 11 ]	= 255,
				[ 12 ]	= 255,
				[ 13 ]	= 64,
				[ 14 ]	= 73,
				[ 15 ]	= 63,
				[ 16 ]	= 72,
				[ 17 ]	= 52,
				[ 18 ]	= 53,
				[ 19 ]	= 54,
				[ 20 ]	= 55,
				[ 21 ]	= 56,
				[ 22 ]	= 57,
				[ 23 ]	= 58,
				[ 24 ]	= 59,
				[ 25 ]	= 60,
				[ 26 ]	= 61,
				[ 27 ]	= 65,
				[ 28 ]	= 66,
				[ 29 ]	= 255,
				[ 30 ]	= 255,
				[ 31 ]	= 255,
				[ 32 ]	= 68,
				[ 33 ]	= 255,
				[ 34 ]	= 0,
				[ 35 ]	= 1,
				[ 36 ]	= 2,
				[ 37 ]	= 3,
				[ 38 ]	= 4,
				[ 39 ]	= 5,
				[ 40 ]	= 6,
				[ 41 ]	= 7,
				[ 42 ]	= 8,
				[ 43 ]	= 9,
				[ 44 ]	= 10,
				[ 45 ]	= 11,
				[ 46 ]	= 12,
				[ 47 ]	= 13,
				[ 48 ]	= 14,
				[ 49 ]	= 15,
				[ 50 ]	= 16,
				[ 51 ]	= 17,
				[ 52 ]	= 18,
				[ 53 ]	= 19,
				[ 54 ]	= 20,
				[ 55 ]	= 21,
				[ 56 ]	= 22,
				[ 57 ]	= 23,
				[ 58 ]	= 24,
				[ 59 ]	= 25,
				[ 60 ]	= 255,
				[ 61 ]	= 255,
				[ 62 ]	= 255,
				[ 63 ]	= 255,
				[ 64 ]	= 255,
				[ 65 ]	= 255,
				[ 66 ]	= 26,
				[ 67 ]	= 27,
				[ 68 ]	= 28,
				[ 69 ]	= 29,
				[ 70 ]	= 30,
				[ 71 ]	= 31,
				[ 72 ]	= 32,
				[ 73 ]	= 33,
				[ 74 ]	= 34,
				[ 75 ]	= 35,
				[ 76 ]	= 36,
				[ 77 ]	= 37,
				[ 78 ]	= 38,
				[ 79 ]	= 39,
				[ 80 ]	= 40,
				[ 81 ]	= 41,
				[ 82 ]	= 42,
				[ 83 ]	= 43,
				[ 84 ]	= 44,
				[ 85 ]	= 45,
				[ 86 ]	= 46,
				[ 87 ]	= 47,
				[ 88 ]	= 48,
				[ 89 ]	= 49,
				[ 90 ]	= 50,
				[ 91 ]	= 51,
			},
			[ "mByteGlyphMapBase" ] = 32,
			[ "mScale" ] = 27,
			[ "mByteGlyphs" ] = {
				[ 1 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.01953125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.74074077606201,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 65,
				},
				[ 2 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.0205078125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.037109375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.62962961196899,
					[ "mAdvanceX" ] = 0.66666668653488,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 66,
				},
				[ 3 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.0380859375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.0537109375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.59259259700775,
					[ "mAdvanceX" ] = 0.66666668653488,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 67,
				},
				[ 4 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.0546875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.072265625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.66666668653488,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 68,
				},
				[ 5 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.0732421875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.0888671875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.59259259700775,
					[ "mAdvanceX" ] = 0.62962961196899,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 69,
				},
				[ 6 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.08984375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.103515625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.55555558204651,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 70,
				},
				[ 7 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.1044921875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.1220703125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.66666668653488,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 71,
				},
				[ 8 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.123046875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.1416015625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.70370370149612,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 72,
				},
				[ 9 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.142578125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.150390625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.29629629850388,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 73,
				},
				[ 10 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.1513671875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.16015625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.33333334326744,
					[ "mAdvanceX" ] = 0.37037038803101,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 74,
				},
				[ 11 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.1611328125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.1796875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.70370370149612,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 75,
				},
				[ 12 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.1806640625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.1953125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.55555558204651,
					[ "mAdvanceX" ] = 0.59259259700775,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 76,
				},
				[ 13 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.1962890625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.2197265625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.88888889551163,
					[ "mAdvanceX" ] = 0.88888889551163,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 77,
				},
				[ 14 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.220703125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.240234375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = -0.037037037312984,
					[ "mWidth" ] = 0.74074077606201,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 78,
				},
				[ 15 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.2412109375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.2578125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.62962961196899,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 79,
				},
				[ 16 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.2587890625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.2724609375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.55555558204651,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 80,
				},
				[ 17 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.2734375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.2900390625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.62962961196899,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 81,
				},
				[ 18 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.291015625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.30859375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.66666668653488,
					[ "mAdvanceX" ] = 0.66666668653488,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 82,
				},
				[ 19 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.3095703125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.3212890625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.074074074625969,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.55555558204651,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 83,
				},
				[ 20 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.322265625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.3359375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.59259259700775,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 84,
				},
				[ 21 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.3369140625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.3564453125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.74074077606201,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 85,
				},
				[ 22 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.357421875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.376953125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.74074077606201,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 86,
				},
				[ 23 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.3779296875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.40234375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.92592591047287,
					[ "mAdvanceX" ] = 0.92592591047287,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 87,
				},
				[ 24 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.4033203125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.4228515625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.74074077606201,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 88,
				},
				[ 25 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.423828125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.4423828125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.70370370149612,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 89,
				},
				[ 26 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.443359375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.4580078125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.55555558204651,
					[ "mAdvanceX" ] = 0.59259259700775,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 90,
				},
				[ 27 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.458984375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.4697265625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.40740740299225,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 97,
				},
				[ 28 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.470703125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.4833984375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 98,
				},
				[ 29 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.484375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.494140625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.37037038803101,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 99,
				},
				[ 30 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.4951171875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.5078125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 100,
				},
				[ 31 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.5087890625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.5185546875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.37037038803101,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 101,
				},
				[ 32 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.51953125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.529296875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.37037038803101,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 102,
				},
				[ 33 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.5302734375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.5419921875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 103,
				},
				[ 34 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.54296875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.556640625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 104,
				},
				[ 35 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.5576171875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.5634765625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.22222222387791,
					[ "mAdvanceX" ] = 0.25925925374031,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 105,
				},
				[ 36 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.564453125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.5712890625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = -0.074074074625969,
					[ "mWidth" ] = 0.25925925374031,
					[ "mAdvanceX" ] = 0.25925925374031,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 106,
				},
				[ 37 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.572265625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.5849609375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.48148149251938,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 107,
				},
				[ 38 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.5859375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.591796875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.22222222387791,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 108,
				},
				[ 39 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.5927734375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.6123046875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.74074077606201,
					[ "mAdvanceX" ] = 0.74074077606201,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 109,
				},
				[ 40 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.61328125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.626953125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 110,
				},
				[ 41 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.6279296875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.6396484375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 111,
				},
				[ 42 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.640625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.6533203125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 112,
				},
				[ 43 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.654296875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.6669921875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 113,
				},
				[ 44 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.66796875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.6767578125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.33333334326744,
					[ "mAdvanceX" ] = 0.33333334326744,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 114,
				},
				[ 45 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.677734375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.685546875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.29629629850388,
					[ "mAdvanceX" ] = 0.37037038803101,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 115,
				},
				[ 46 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.6865234375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.6943359375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.29629629850388,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 116,
				},
				[ 47 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.6953125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.708984375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 117,
				},
				[ 48 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.7099609375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.72265625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = -0.037037037312984,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 118,
				},
				[ 49 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.7236328125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.7421875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.70370370149612,
					[ "mAdvanceX" ] = 0.70370370149612,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 119,
				},
				[ 50 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.7431640625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.755859375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.48148149251938,
					[ "mAdvanceX" ] = 0.48148149251938,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 120,
				},
				[ 51 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.7568359375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.7705078125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = -0.037037037312984,
					[ "mWidth" ] = 0.51851850748062,
					[ "mAdvanceX" ] = 0.48148149251938,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 121,
				},
				[ 52 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.771484375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.7822265625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.40740740299225,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 122,
				},
				[ 53 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.783203125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.794921875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 48,
				},
				[ 54 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.7958984375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.802734375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.074074074625969,
					[ "mWidth" ] = 0.25925925374031,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 49,
				},
				[ 55 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.8037109375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.8154296875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 50,
				},
				[ 56 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.81640625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.8271484375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.40740740299225,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 51,
				},
				[ 57 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.828125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.83984375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 52,
				},
				[ 58 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.8408203125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.8515625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mKernTable" ] = {
						[ 1 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 55,
						},
						[ 2 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 57,
						},
						[ 3 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 58,
						},
					},
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.40740740299225,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 53,
				},
				[ 59 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.8525390625,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.8642578125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 54,
				},
				[ 60 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.865234375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.8759765625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mKernTable" ] = {
						[ 1 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 68,
						},
						[ 2 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 70,
						},
						[ 3 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 72,
						},
						[ 4 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 76,
						},
						[ 5 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 82,
						},
						[ 6 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 85,
						},
						[ 7 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 86,
						},
						[ 8 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 88,
						},
						[ 9 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 90,
						},
					},
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.40740740299225,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 55,
				},
				[ 61 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.876953125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.8876953125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.40740740299225,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 56,
				},
				[ 62 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.888671875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.900390625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mKernTable" ] = {
						[ 1 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.11111111193895,
							[ "mName" ] = 68,
						},
						[ 2 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.11111111193895,
							[ "mName" ] = 72,
						},
						[ 3 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 76,
						},
						[ 4 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.11111111193895,
							[ "mName" ] = 82,
						},
						[ 5 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 85,
						},
						[ 6 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 88,
						},
					},
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.44444444775581,
					[ "mAdvanceX" ] = 0.51851850748062,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 57,
				},
				[ 63 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0.25925925374031,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 32,
				},
				[ 64 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9013671875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9033203125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.074074074625969,
					[ "mWidth" ] = 0.074074074625969,
					[ "mAdvanceX" ] = 0.25925925374031,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 46,
				},
				[ 65 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.904296875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.908203125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.14814814925194,
					[ "mAdvanceX" ] = 0.25925925374031,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 44,
				},
				[ 66 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9091796875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9111328125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mKernTable" ] = {
						[ 1 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 68,
						},
						[ 2 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 72,
						},
						[ 3 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 76,
						},
						[ 4 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 82,
						},
						[ 5 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 85,
						},
						[ 6 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.037037037312984,
							[ "mName" ] = 88,
						},
					},
					[ "mBearingX" ] = 0.074074074625969,
					[ "mWidth" ] = 0.074074074625969,
					[ "mAdvanceX" ] = 0.22222222387791,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 58,
				},
				[ 67 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.912109375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.916015625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.074074074625969,
					[ "mWidth" ] = 0.14814814925194,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 59,
				},
				[ 68 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9169921875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9189453125,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.11111111193895,
					[ "mWidth" ] = 0.074074074625969,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 33,
				},
				[ 69 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.919921875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9287109375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.074074074625969,
					[ "mWidth" ] = 0.33333334326744,
					[ "mAdvanceX" ] = 0.44444444775581,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 63,
				},
				[ 70 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9296875,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9365234375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.25925925374031,
					[ "mAdvanceX" ] = 0.33333334326744,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 40,
				},
				[ 71 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9443359375,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.25925925374031,
					[ "mAdvanceX" ] = 0.33333334326744,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 41,
				},
				[ 72 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9453125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.9638671875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.70370370149612,
					[ "mAdvanceX" ] = 0.77777779102325,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 38,
				},
				[ 73 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.96484375,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.97265625,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mKernTable" ] = {
						[ 1 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 55,
						},
						[ 2 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 57,
						},
						[ 3 ]	= {
							[ "mY" ] = 0,
							[ "mX" ] = -0.074074074625969,
							[ "mName" ] = 58,
						},
					},
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0.29629629850388,
					[ "mAdvanceX" ] = 0.29629629850388,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 47,
				},
				[ 74 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0.5625,
						[ "mXMin" ] = 0.9736328125,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0.98046875,
					},
					[ "mHeight" ] = 1.3333333730698,
					[ "mBearingX" ] = 0.037037037312984,
					[ "mWidth" ] = 0.25925925374031,
					[ "mAdvanceX" ] = 0.33333334326744,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 45,
				},
				[ 75 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 76 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 77 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 78 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 79 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 80 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 81 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 82 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 83 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 84 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 85 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 86 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 87 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 88 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 89 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 90 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
				[ 91 ]	= {
					[ "mUVRect" ] = {
						[ "mYMax" ] = 0,
						[ "mXMin" ] = 0,
						[ "mYMin" ] = 0,
						[ "mXMax" ] = 0,
					},
					[ "mHeight" ] = 0,
					[ "mBearingX" ] = 0,
					[ "mWidth" ] = 0,
					[ "mAdvanceX" ] = 0,
					[ "mYOff" ] = 0,
					[ "mCode" ] = 4294967295,
				},
			},
			[ "mLineSpacing" ] = 1.1481481790543,
		}
	)

end

--Declaring Objects
local objects = {

	--Declaring Tables
	[ 0x021B4380 ] = {},

	--Declaring Instances
	[ 0x021D3F9C ] = serializer:registerObjectID ( MOAIFont.new (), 0x021D3F9C ),

}

init ( objects )

--Returning Tables
return objects [ 0x021D3F9C ]
