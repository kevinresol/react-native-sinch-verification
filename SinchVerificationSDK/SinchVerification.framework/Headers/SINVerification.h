/*
 * Copyright (c) 2016 Sinch AB. All rights reserved.
 *
 * See LICENSE file for license terms and information.
 */

#import <Foundation/Foundation.h>
#import "SINExport.h"
#import "SINLog.h"

/**
 * The SINVerification is the entry point of the Sinch Verification SDK.
 *
 * ### Example
 *
 * 	 NSError *error = nil;
 * 	 id<SINPhoneNumber> phoneNumber = [SINPhoneNumberUtil() parse:@"415 555 0101"
 * 	                                              defaultRegion:@"US"
 * 	                                                      error:&error];
 * 	 
 * 	 NSString* phoneNumberE164 = [SINPhoneNumberUtil() formatNumber:phoneNumber
 * 	                                                         format:SINPhoneNumberFormatE164];
 *
 * 	 id<SINVerification> verification = [SINVerification SMSVerificationWithApplicationKey:@"<APPKEY>"
 * 	                                                                          phoneNumber:phoneNumberE164];
 *
 * 	 [self.verification initiateWithCompletionHandler:^(BOOL success, NSError *error) {
 * 	   // verification initiated, user will now receive an SMS to their phone.
 * 	 }];
 *
 * 	 NSString* code; // get user to input code received in SMS
 *
 * 	 [self.verification verifyCode:(NSString*) code completionHandler:^(BOOL success, NSError *error) {
 * 	   // verification completed
 * 	 }];
 */

NS_ASSUME_NONNULL_BEGIN

@protocol SINVerification;

SIN_EXPORT
@interface SINVerification : NSObject

/**
 * Instantiate a new SMS-based verification.
 *
 * @return A new SMS-based SINVerification instance.
 *
 * @param applicationKey Application key identifying the application.
 *
 * @param phoneNumber The phone number to verify.
 *                    The phone number should be given according to E.164 number formatting
 *                    (http://en.wikipedia.org/wiki/E.164) and should be prefixed with a '+'.
 *                    E.g. to call the US phone number 415 555 0101, it should be specified as
 *                    "+14155550101", where the '+' is the required prefix and the US country
 *                    code '1' added before the local subscriber number.
 *
 * @see SINPhoneNumberUtil for formatting a phone number in E.164 format.
 *
 */
+ (id<SINVerification>)SMSVerificationWithApplicationKey:(NSString*)applicationKey phoneNumber:(NSString*)phoneNumber;

/**
 * Instantiate a new SMS-based verification.
 *
 * @return A new SMS-based SINVerification instance.
 *
 * @param applicationKey Application key identifying the application.
 *
 * @param phoneNumber The phone number to verify.
 *                    The phone number should be given according to E.164 number formatting
 *                    (http://en.wikipedia.org/wiki/E.164) and should be prefixed with a '+'.
 *                    E.g. to call the US phone number 415 555 0101, it should be specified as
 *                    "+14155550101", where the '+' is the required prefix and the US country
 *                    code '1' added before the local subscriber number.
 *
 * @param custom      Application-specific custom data that will be passed to
 *                    REST API callbacks made to the application's backend.
 *                    This custom data will also be written to CDRs (Call Detail Records).
 *                    (If complex data is to be passed along, it must first be encoded as a
 *                    NSString*, e.g. encoded as JSON or Base64.)
 *
 * @see SINPhoneNumberUtil for formatting a phone number in E.164 format.
 *
 */
+ (id<SINVerification>)SMSVerificationWithApplicationKey:(NSString*)applicationKey
                                             phoneNumber:(NSString*)phoneNumber
                                                  custom:(NSString*)custom;

/**
 * Instantiate a new Callout-based verification. The Sinch backend
 * will call out to the given phone number to verify the phone number.
 *
 * @return A new Callout-based SINVerification instance.
 *
 * @param applicationKey Application key identifying the application.
 *
 * @param phoneNumber The phone number to verify.
 *                    The phone number should be given according to E.164 number formatting
 *                    (http://en.wikipedia.org/wiki/E.164) and should be prefixed with a '+'.
 *                    E.g. to call the US phone number 415 555 0101, it should be specified as
 *                    "+14155550101", where the '+' is the required prefix and the US country
 *                    code '1' added before the local subscriber number.
 *
 * @see SINPhoneNumberUtil for formatting a phone number in E.164 format.
 *
 */
+ (id<SINVerification>)calloutVerificationWithApplicationKey:(NSString*)applicationKey
                                                 phoneNumber:(NSString*)phoneNumber;

/**
 * Instantiate a new Callout-based verification. The Sinch backend
 * will call out to the given phone number to verify the phone number.
 *
 * @return A new Callout-based SINVerification instance.
 *
 * @param applicationKey Application key identifying the application.
 *
 * @param phoneNumber The phone number to verify.
 *                    The phone number should be given according to E.164 number formatting
 *                    (http://en.wikipedia.org/wiki/E.164) and should be prefixed with a '+'.
 *                    E.g. to call the US phone number 415 555 0101, it should be specified as
 *                    "+14155550101", where the '+' is the required prefix and the US country
 *                    code '1' added before the local subscriber number.
 *
 * @param custom      Application-specific custom data that will be passed to
 *                    REST API callbacks made to the application's backend.
 *                    This custom data will also be written to CDRs (Call Detail Records).
 *                    (If complex data is to be passed along, it must first be encoded as a
 *                    NSString*, e.g. encoded as JSON or Base64.)
 *
 * @see SINPhoneNumberUtil for formatting a phone number in E.164 format.
 *
 */
+ (id<SINVerification>)calloutVerificationWithApplicationKey:(NSString*)applicationKey
                                                 phoneNumber:(NSString*)phoneNumber
                                                      custom:(NSString*)custom;

/**
 * Returns the Sinch Verification SDK version.
 */
+ (NSString*)version;

/**
 * Set a log callback block.
 *
 * The Sinch Verification SDK will emit all it's logging by invoking the specified block.
 *
 * @param block log callback block. IMPORTANT: The block may be invoked on any thread / GCD queue.
 *
 */
+ (void)setLogCallback:(__nullable SINLogCallback)block;

@end

@protocol SINVerification <NSObject>

@required
/**
 * Initiate the verification.
 *
 * A request will be sent to the Sinch backend, which in case of SMS-based verification,
 * will initiate sending an SMS to the destination phone number.
 *
 * @param completionHandler Block that will be invoked upon successful initiation.
 */
- (void)initiateWithCompletionHandler:(void (^)(BOOL success, NSError* __nullable error))completionHandler;

/**
 * Complete the verification by verifying the verification code sent to the user.
 *
 * @param code Verification code that the user received and have given as input to the application.
 *
 * @param completionHandler Block that will be invoked upon successful initiation.
 */
- (void)verifyCode:(NSString*)code
    completionHandler:(void (^)(BOOL success, NSError* __nullable error))completionHandler;

/**
 * Cancel the verification (client-side only).
 *
 * Note that cancelling is a client-side only action, i.e. it will not send any
 * further requests to the Sinch platform and it does not guarantee that a SMS
 * or a callout won't be made to the user's device. What it will do is cancel any
 * long-polling requests that this verification instance may be maintaining (e.g.
 * a callout verification is performing polling to query the Sinch platform for
 * the status of the verification)
 *
 * If the verification is in a state where a completion handler have been specified,
 * the handler will be invoked with the error code SINVerificationErrorCancelled.
 *
 */
- (void)cancel;

/**
 * Specify a specific Sinch environment host. (This is not mandatory)
 * This must be set before initiateWithCompletionHandler: or verifyCode:completionHandler: is called.
 *
 * @param environmentHost Host for base URL for the Sinch API environment to be used. E.g. 'sandbox.sinch.com'
 */
@required
- (void)setEnvironmentHost:(NSString*)environmentHost;

/**
 * Specify a dispatch queue on which `completionHandler` blocks of a SINVerification
 * should be invoked on. Unless specified, the main queue is used by default.
 * This must be set before initiateWithCompletionHandler: or verifyCode:completionHandler: is called.
 *
 * @param completionQueue GCD dispatch queue
 */
@required
- (void)setCompletionQueue:(dispatch_queue_t)completionQueue;

@end

// NSNotifications that can be used to observe progress of a verification
SIN_EXTERN NSString* const SINVerificationDidBeginInitiatingNotification;
SIN_EXTERN NSString* const SINVerificationDidEndInitiatingNotification;
SIN_EXTERN NSString* const SINVerificationDidBeginVerifyingCodeNotification;
SIN_EXTERN NSString* const SINVerificationDidEndVerifyingCodeNotification;
SIN_EXTERN NSString* const SINVerificationDidBeginVerifyingCalloutNotification;
SIN_EXTERN NSString* const SINVerificationDidEndVerifyingCalloutNotification;

NS_ASSUME_NONNULL_END
