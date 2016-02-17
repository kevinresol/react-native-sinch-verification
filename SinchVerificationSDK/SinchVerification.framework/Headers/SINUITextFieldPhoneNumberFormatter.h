/*
 * Copyright (c) 2016 Sinch AB. All rights reserved.
 *
 * See LICENSE file for license terms and information.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SINExport.h"
#import "SINPhoneNumberFormat.h"

/**
 * SINUITextFieldPhoneNumberFormatter is a helper to perform
 * As-You-Type-Formatting on a UITextField. The formatter performs
 * formatting based on the region country code given at
 * initialization.
 *
 * Example usage:
 *
 * 	// Assuming the following properties:
 * 	@property UITextField* textField;
 * 	@property SINUITextFieldPhoneNumberFormatter* formatter;
 *
 * 	self.formatter = [[SINUITextFieldPhoneNumberFormatter alloc] init];
 * 	self.formatter.textField = self.textField;
 * 	self.textField.placeholder = [self.formatter exampleNumberWithFormat:
 * 	                               SINPhoneNumberFormatNational];
 */

@protocol SINPhoneNumberUtil;

NS_ASSUME_NONNULL_BEGIN

SIN_EXPORT
@interface SINUITextFieldPhoneNumberFormatter : NSObject

@property (nonatomic, copy, readwrite) NSString* countryCode;
@property (nonatomic, strong, readwrite, nullable) UITextField* textField;

/**
 * onTextFieldTextDidChange is a block that is invoked when the text value of
 * the observed UITextField changes. This callback handles both events
 * from UITextFieldTextDidChangeNotification and KVO-events for the
 * UITextField.text property.
 *
 * It can be used to implement additional hooks like indicating to the
 * user whether the current input is a possibly valid phone number,
 * e.g. with -[SINPhoneNumberUtil isPossibleNumber:error:].
 */
@property (nonatomic, copy, readwrite, nullable) void (^onTextFieldTextDidChange)(UITextField*);

/**
 * Default initialization. Equivalent to initializing with
 * SINPhoneNumberUtil() and +[SINDeviceRegion currentCountryCode].
 */
- (instancetype)init;

/**
 *
 * @param isoCountryCode ISO 3166-1 two-letter country code that
 *                       indicates the country/region where the phone
 *                       number is being entered.
 *
 */
- (instancetype)initWithCountryCode:(NSString*)isoCountryCode;

/**
 * Designated initializer.
 *
 * @param phoneNumberUtil instance of utility class that will be used
 *                        for phone number parsing and formatting.
 *
 * @param isoCountryCode ISO 3166-1 two-letter country code that
 *                       indicates the country/region where the phone
 *                       number is being entered.
 */
- (instancetype)initWithPhoneNumberUtil:(id<SINPhoneNumberUtil>)phoneNumberUtil countryCode:(NSString*)isoCountryCode;

/**
 * Get a an example phone number formatted according to given format.
 *
 * The returned string can be used as placeholder text for a
 * UITextField.
 *
 * @return a formatted phone number string. Will return an empty
 *         string if no example phone number is available for the
 *         given region country code.
 */
- (NSString*)exampleNumberWithFormat:(SINPhoneNumberFormat)format;

@end

NS_ASSUME_NONNULL_END
