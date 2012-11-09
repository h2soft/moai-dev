//----------------------------------------------------------------//
// Copyright (c) 2012 H2SOFT Co., Ltd
// All Rights Reserved. 
// http://www.h2soft.kr
//----------------------------------------------------------------//
package com.ziplinegames.moai;

import android.app.Activity;
import android.view.View;
import android.view.Gravity;
import android.view.ViewManager;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

import com.google.ads.*;


//================================================================//
// MoaiAdMob
//================================================================//
public class MoaiAdMob {

	private static Activity sActivity = null;
	private static AdView sAdView;
	
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
		FrameLayout parent = ( FrameLayout ) sActivity.findViewById( android.R.id.content );
		
		sAdView = new AdView ( sActivity, AdSize.BANNER, adUnitId );
		FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams (
				                FrameLayout.LayoutParams.WRAP_CONTENT,
				                FrameLayout.LayoutParams.WRAP_CONTENT, Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL );
		parent.addView ( sAdView, layoutParams );
		sAdView.loadAd ( new AdRequest () );
	}
	
	//----------------------------------------------------------------//	
	public static void dismiss ( ) {
		if ( sAdView != null ) {
			sAdView.destroy ( );
			(( ViewManager ) sAdView.getParent ()).removeView ( sAdView );
			sAdView = null;
		}
	}
}
