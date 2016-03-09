var React = require('react-native');
var NativeModules = React.NativeModules;
var Platform = React.Platform;
var invariant = require('invariant');
var SinchVerificationIOS = NativeModules.SinchVerificationIOS;
var SinchVerificationAndroid = NativeModules.SinchVerificationAndroid;

var SinchVerification;
if (Platform.OS === 'ios') {
    invariant(SinchVerificationIOS, 'Add SinchVerificationIOS.h and SinchVerificationIOS.m to your Xcode project');
    SinchVerification = SinchVerificationIOS;
} else if (Platform.OS === 'android') {
    invariant(SinchVerificationAndroid, 'Import libraries to android "rnpm link"');
    SinchVerification = SinchVerificationAndroid;
} else {
    invariant(SinchVerification, "Invalid platform");
}

var applicationKey = null;

module.exports = {
	
	init: function(appKey) {
		applicationKey = appKey;
	},
	
	sms: function(phoneNumber, custom, callback) {
		invariant(applicationKey, 'Call init() to setup the Sinch application key.');
		SinchVerification.sms(applicationKey, phoneNumber, custom, callback);
	},
	
	flashCall: function(phoneNumber, custom, callback) {
		invariant(applicationKey, 'Call init() to setup the Sinch application key.');
		SinchVerification.flashCall(applicationKey, phoneNumber, custom, callback);
	},
	
	verify: SinchVerification.verify,
	
}