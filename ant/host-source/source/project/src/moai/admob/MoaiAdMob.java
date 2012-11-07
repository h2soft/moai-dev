//----------------------------------------------------------------//
// Copyright (c) 2012 H2SOFT Co., Ltd
// All Rights Reserved. 
// http://www.h2soft.kr
//----------------------------------------------------------------//
package com.ziplinegames.moai;

import android.app.Activity;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.view.Gravity;

import com.google.ads.*;


//================================================================//
// MoaiAdMob
//================================================================//
public class MoaiAdMob {

	private static Activity sActivity = null;
	private static AdView adView;
	
	//----------------------------------------------------------------//
	public static void onCreate ( Activity activity ) {
		sActivity = activity;
	}

	public static void onStart () {
	}

	public static void onStop () {
	}
	
	//================================================================//
	// AdMob JNI callback methods
	//================================================================//
	
	//----------------------------------------------------------------//	
	public static void showBanner ( String adUnitId ) {
		FrameLayout parent = ( FrameLayout ) sActivity.findViewById(android.R.id.content);
		
		adView = new AdView ( sActivity, AdSize.BANNER, adUnitId );
		FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
				                FrameLayout.LayoutParams.WRAP_CONTENT,
				                FrameLayout.LayoutParams.WRAP_CONTENT, Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL );
		parent.addView ( adView, layoutParams );
		adView.loadAd ( new AdRequest () );
	}
	
	//----------------------------------------------------------------//	
	public static void dismiss ( ) {
		if ( adView != null ) {
			adView.destroy();
		}
	}
}
