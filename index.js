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

module.exports = SinchVerification;