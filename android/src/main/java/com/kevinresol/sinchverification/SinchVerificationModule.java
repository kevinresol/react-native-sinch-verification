package com.kevinresol.sinchverification;

import com.facebook.react.modules.network.ForwardingCookieHandler;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableMap;

import com.sinch.verification.CodeInterceptionException;
import com.sinch.verification.Config;
import com.sinch.verification.IncorrectCodeException;
import com.sinch.verification.InvalidInputException;
import com.sinch.verification.ServiceErrorException;
import com.sinch.verification.SinchVerification;
import com.sinch.verification.Verification;
import com.sinch.verification.VerificationListener;
import com.sinch.verification.PhoneNumberUtils;

import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URI;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class SinchVerificationModule extends ReactContextBaseJavaModule {

    private ReactApplicationContext mContext;
    private Verification mVerification;
    private Callback mCallback;
	
    public SinchVerificationModule(ReactApplicationContext context) {
        super(context);
        mContext = context;
    }

    public String getName() {
        return "SinchVerificationAndroid";
    }

    @ReactMethod
    public void reset(Callback callback) {
        mVerification = null;
        callback.invoke(null, null);
    }

    @ReactMethod
    public void flashCall(String applicationKey, String phoneNumber, String custom, Callback callback) {
        mCallback = callback;
        Config config = SinchVerification.config().applicationKey(applicationKey).context(mContext).build();
        VerificationListener listener = new MyVerificationListener();
        String defaultRegion = PhoneNumberUtils.getDefaultCountryIso(mContext);
        String phoneNumberInE164 = PhoneNumberUtils.formatNumberToE164(phoneNumber, defaultRegion);
        mVerification = SinchVerification.createFlashCallVerification(config, phoneNumberInE164, custom, listener);
        mVerification.initiate();
    }

    @ReactMethod
    public void sms(String applicationKey, String phoneNumber, String custom, final Callback callback) {
        mCallback = callback;
        Config config = SinchVerification.config().applicationKey(applicationKey).context(mContext).build();
        VerificationListener listener = new MyVerificationListener();
        String defaultRegion = PhoneNumberUtils.getDefaultCountryIso(mContext);
        String phoneNumberInE164 = PhoneNumberUtils.formatNumberToE164(phoneNumber, defaultRegion);
        mVerification = SinchVerification.createSmsVerification(config, phoneNumberInE164, custom, listener);
        mVerification.initiate();
    }

    @ReactMethod
    public void verify(String code, final Callback callback) {
        if (mVerification == null) {
            callback.invoke("Verification object not found. Did you call flashCall() or sms() first?", null);
            return;
        }
        mCallback = callback;
        mVerification.verify(code);
    }

    private void consumeCallback(Boolean success, WritableMap payload) {
        if (mCallback != null) {
            if (success) {
                mCallback.invoke(null, payload);
            } else {
                mCallback.invoke(payload, null);
            }
            mCallback = null;
        }
    }

    private class MyVerificationListener implements VerificationListener{

        public void onInitiated() {

        }

        public void onInitiationFailed(Exception e)  {
            WritableMap map = Arguments.createMap();
            map.putString("message", e.getMessage());
            consumeCallback(false, map);
        }

        public void onVerified() {
            consumeCallback(true, null);
        }

        public void onVerificationFailed(Exception e) {
            WritableMap map = Arguments.createMap();
            if (e instanceof InvalidInputException) {
                // Incorrect number or code provided
            } else if (e instanceof CodeInterceptionException) {
                // Intercepting the verification code automatically failed, input the code manually with verify()
            } else if (e instanceof IncorrectCodeException) {
                // The verification code provided was incorrect
            } else if (e instanceof ServiceErrorException) {
                // Sinch service error
            } else {
                // Other system error, such as UnknownHostException in case of network error
            }
			map.putString("message", e.getMessage());
            consumeCallback(false, map);
        }
    }
}
