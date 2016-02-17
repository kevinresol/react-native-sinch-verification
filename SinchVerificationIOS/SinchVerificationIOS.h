#import <SinchVerification/SinchVerification.h>

#import "RCTBridgeModule.h"


@interface SinchVerificationIOS : NSObject <RCTBridgeModule>

@property (strong, nonatomic) id<SINVerification> verification;
@property (nonatomic, strong) NSString* applicationKey;


@end