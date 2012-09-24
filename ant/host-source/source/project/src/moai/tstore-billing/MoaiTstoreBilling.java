package com.ziplinegames.moai;

import android.app.Activity;

import com.feelingk.iap.IAPActivity;
import com.feelingk.iap.IAPLib;
import com.feelingk.iap.IAPLib.OnClientListener;
import com.feelingk.iap.IAPLibSetting;
import com.feelingk.iap.net.ItemAuth;
import com.feelingk.iap.net.ItemAuthInfo;
import com.feelingk.iap.net.ItemUse;

//================================================================//
// MoaiTstoreBilling
//================================================================//
public class MoaiTstoreBilling {

	private static MoaiTstoreActivity sActivity = null;
	
	protected static native void	AKUNotifyTstorePurchaseComplete	( );
	protected static native void	AKUNotifyTstorePurchaseCancel	( );
	protected static native void	AKUNotifyTstorePurchaseError	( int errorCode, int subErrorCode );
	
	//----------------------------------------------------------------//
	public static void onCreate( Activity activity ) {
		sActivity = (MoaiTstoreActivity) activity;
	}

	public static void onStart() {
	}

	public static void onStop() {
	}
	
	public static void onDestroy() {
	}
	
	//================================================================//
	// Tstore JNI callback methods
	//================================================================//
	public static void setApplicationId(String appId) {
    IAPLibSetting setting   = new IAPLibSetting(); 
    setting.AppID           = appId;
    setting.BP_IP           = null;
    setting.BP_Port         = 0;
		setting.ClientListener  = sListener;
		sActivity.IAPLibInit(setting);
	}
	
	public static void requestPurchase(String productId) {
		sActivity.requestPurchase(productId);
	}
	
	
  static OnClientListener sListener = new OnClientListener() {
		public void onItemPurchaseComplete() {
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyTstorePurchaseComplete ( );
			}
		}
		
		@Override
		public void onDlgPurchaseCancel() {
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyTstorePurchaseCancel ( );
			}
		}

		@Override
		public void onError(int errorCode, int subErrorCode) {    
			synchronized ( Moai.sAkuLock ) {
				AKUNotifyTstorePurchaseError ( errorCode, subErrorCode );
			}
		}
		
		public Boolean onItemQueryComplete() {
			return true;
		}
    
		public void onWholeQuery(ItemAuth[] items) {}
		public void onItemUseQuery(ItemUse item) {}
		public void onItemAuthInfo(ItemAuthInfo itemAuth) {}
		
		@Override
		public void onDlgError() {}

		@Override
		public void onJuminNumberDlgCancel() {}

		@Override
		public void onDlgAutoPurchaseInfoCancel() {}

		@Override
		public void onJoinDialogCancel() {}

		@Override
		public void onPurchaseDismiss() {}
	};
}
