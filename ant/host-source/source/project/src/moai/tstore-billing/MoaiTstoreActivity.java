package com.ziplinegames.moai;

import com.feelingk.iap.IAPActivity;

//================================================================//
// MoaiTstoreActivity
//================================================================//
public class MoaiTstoreActivity extends IAPActivity {
	public void requestPurchase(String productId) {
		popPurchaseDlg(productId, null, null, null);
	}
}
