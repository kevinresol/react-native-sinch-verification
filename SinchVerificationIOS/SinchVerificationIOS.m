#import "SinchVerificationIOS.h"
#import "RCTConvert.h"
#import <SinchVerification/SinchVerification.h>

@implementation SinchVerificationIOS

RCT_EXPORT_MODULE()

RCT_EXPORT_METHOD(init:(NSString *)appKey callback:(RCTResponseSenderBlock)callback) {
	_applicationKey = appKey;
	callback(@[[NSNull null]]);
}

RCT_EXPORT_METHOD(sms:(NSString *)phoneNumber custom:(NSString *)custom callback:(RCTResponseSenderBlock)callback) {
    // Get user's current region by carrier info
    NSString* defaultRegion = [SINDeviceRegion currentCountryCode];
    defaultRegion=@"HK";
    NSError *parseError = nil;
    id<SINPhoneNumber> _phoneNumber = [SINPhoneNumberUtil() parse:phoneNumber
                                                   defaultRegion:defaultRegion
                                                           error:&parseError];
    if (!_phoneNumber){
        callback(@[@"Invalid phone number"]);
    }

    NSString *phoneNumberInE164 = [SINPhoneNumberUtil() formatNumber:_phoneNumber
                                                              format:SINPhoneNumberFormatE164];
    NSLog(phoneNumberInE164);
    id<SINVerification> verification = [SINVerification SMSVerificationWithApplicationKey:_applicationKey
                                                                              phoneNumber:phoneNumberInE164
                                                                                   custom:custom];
    self.verification = verification; // retain the verification instance
    [verification initiateWithCompletionHandler:^(BOOL success, NSError *error) {
        if (success) {
            callback(@[[NSNull null]]);
        }
    }];
}

RCT_EXPORT_METHOD(verify:(NSString *)code callback:(RCTResponseSenderBlock)callback) {
  [self.verification verifyCode:code
              completionHandler:^(BOOL success, NSError* error) {
                if (success) {
                  callback(@[[NSNull null]]);
                } else {
                  callback(@[@"Invalid code"]);
                }
              }];
}



@end
