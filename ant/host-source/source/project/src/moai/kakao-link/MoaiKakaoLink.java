package com.ziplinegames.moai;

import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;


// Copyright 2011 Kakao Corp. All rights reserved.
// 
// @author kakaolink@kakao.com
// @version 1.0

public class MoaiKakaoLink {

  private static Activity sActivity = null;

  private static String KakaoLinkApiVersion = "2.0";
  private static String KakaoLinkURLBaseString = "kakaolink://sendurl";
  
  private static Charset KakaoLinkCharset = Charset.forName("UTF-8");
  private static String KakaoLinkEncoding = KakaoLinkCharset.name();
  
  private static String params;

  public static void onCreate( Activity activity ) {
    MoaiLog.i ( "MoaiKakaoLink onCreate : init ");

    sActivity = activity;
  }

  public static void onStart() {
  }
  
  public static void onStop() {
  }
  
  public static void onDestroy() {
  }
  
  // Opens kakaoLink for parameter.
  // 
  // @param activity
  // @param params

  // public static void openKakaoLink(String params) {
    // Intent intent = new Intent(Intent.ACTION_SEND, Uri.parse(params));
    // sActivity.startActivity(intent);
  // }

  // Opens kakaoLink URL for parameters.
  // 
  // @param activity
  // @param url
  // @param message
  // @param appId
             // your application ID
  // @param appVer
             // your application version
  // @param appName
             // your application name
  // @param encoding
             // recommend UTF-8

  public static boolean openKakaoLink(String url, String message, String appId, String appVer, String appName, String encoding) {

    if (isEmptyString(url) || isEmptyString(message) || isEmptyString(appId) || isEmptyString(appVer) || isEmptyString(appName) || isEmptyString(encoding))
      throw new IllegalArgumentException();

    try {
      if (KakaoLinkCharset.equals(Charset.forName(encoding)))
        message = new String(message.getBytes(encoding), KakaoLinkEncoding);
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    }

    params = getBaseKakaoLinkUrl();

    appendParam("url", url);
    appendParam("msg", message);
    appendParam("apiver", KakaoLinkApiVersion);
    appendParam("appid", appId);
    appendParam("appver", appVer);
    appendParam("appname", appName);
    appendParam("type", "link");

    if (isAvailableIntent()) {
      Intent intent = new Intent(Intent.ACTION_SEND, Uri.parse(params));
      sActivity.startActivity(intent);
      return true;
    }
    return false;
  }

  public static void appendParam(final String name, final String value) {
    try {
      String encodedValue = URLEncoder.encode(value, KakaoLinkEncoding);
      params = params + name + "=" + encodedValue + "&";
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    }
  }

  public static boolean isAvailableIntent() {
    Uri kakaoLinkTestUri = Uri.parse(KakaoLinkURLBaseString);
    Intent intent = new Intent(Intent.ACTION_SEND, kakaoLinkTestUri);
    List<ResolveInfo> list = sActivity.getPackageManager().queryIntentActivities(intent, PackageManager.MATCH_DEFAULT_ONLY);
    if (list == null)
      return false;
    return list.size() > 0;
  }

  public static boolean isEmptyString(String str) {
    return (str == null || str.trim().length() == 0);
  }

  public static void appendMetaInfo(ArrayList<Map<String, String>> metaInfoArray) {
    params += "metainfo=";

    JSONObject obj = new JSONObject();
    JSONArray arr = new JSONArray();

    try {
      for (Map<String, String> metaInfo : metaInfoArray) {
        JSONObject metaObj = new JSONObject();
        for (String key : metaInfo.keySet()) {
          metaObj.put(key, metaInfo.get(key));
        }
        arr.put(metaObj);
      }
      obj.put("metainfo", arr);
    } catch (JSONException e) {
      e.printStackTrace();
    }

    try {
      String encodedValue = URLEncoder.encode(obj.toString(), KakaoLinkEncoding);
      params += encodedValue;
    } catch (UnsupportedEncodingException e) {
      e.printStackTrace();
    }
  }

  public static String getBaseKakaoLinkUrl() {
    return KakaoLinkURLBaseString + "?";
  }
}
