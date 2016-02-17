/*
 * Copyright (c) 2016 Sinch AB. All rights reserved.
 *
 * See LICENSE file for license terms and information.
 */

#import <Foundation/Foundation.h>
#import "SINPhoneNumberFormat.h"
#import "SINExport.h"

@protocol SINPhoneNumber;
@protocol SINAsYouTypeFormatter;
@protocol SINRegionList;

NS_ASSUME_NONNULL_BEGIN

SIN_EXPORT SIN_EXTERN NSString *const SINPhoneNumberParseErrorDomain;
SIN_EXPORT SIN_EXTERN NSString *const SINPhoneNumberValidationErrorDomain;
SIN_EXPORT SIN_EXTERN NSString *const SINPhoneNumberRawInputKey;
SIN_EXPORT SIN_EXTERN NSString *const SINPhoneNumberCountryCodeKey;

typedef NS_ENUM(NSInteger, SINPhoneNumberParseError) {
  SINPhoneNumberParseErrorInvalidCountryCode,  // Invalid ISO 3166-1 region / country code.
  SINPhoneNumberParseErrorNotANumber,          // Not a phone number
  SINPhoneNumberParseErrorTooShortAfterIDD,    // Too short after Interational Dialing Prefix
  SINPhoneNumberParseErrorTooShortNSN,         // Too short national number
  SINPhoneNumberParseErrorTooLongNSN,          // To long national number
};

typedef NS_ENUM(NSInteger, SINPhoneNumberValidationError) {
  SINPhoneNumberValidationErrorInvalidCountryCode,  // Invalid ISO 3166-1 region / country code.
  SINPhoneNumberValidationErrorNotANumber,
  SINPhoneNumberValidationErrorTooShort,
  SINPhoneNumberValidationErrorTooLong,

  // Used for stricter checks than "is possible?" / "is viable?",
  // i.e. it is not only not a viable phone number, it also definitely
  // not a valid phone number.
  SINPhoneNumberValidationErrorInvalidNumber,
};

/**
 * IMPORTANT: SINPhoneNumberUtil is _not_ thread-safe.
 */

@protocol SINPhoneNumberUtil <NSObject>

/**
 * Parses a string as a phone number. The phone number is an opaque type
 *
 * @param string input to parse.
 *
 * @param isoCountryCode default region as ISO-3166-1 country code.
 *
 * @param error will be assigned if the string cannot be parsed
 *              as a valid phone number.
 *
 * @return a phone number instance, or nil if the input cannot be
 *         parsed as a valid phone number.
 *
 * @see To format the parsed phone number, use -[SINPhoneNumberUtil formatNumber:format:].
 */
- (nullable id<SINPhoneNumber>)parse:(NSString *)string
                       defaultRegion:(NSString *)isoCountryCode
                               error:(NSError **)error;

/**
 * Format a phone number in the specified format.
 *
 * @param phoneNumber a phone number instance.
 *
 * @param format a format specifier, e.g. E.164, National or
 *               International format.
 *
 * @return formatted string. Returns empty string if input is invalid.
 */
- (NSString *)formatNumber:(id<SINPhoneNumber>)phoneNumber format:(SINPhoneNumberFormat)format;

/**
 * Get an example phone number.
 *
 * Defaults to returning a Mobile example number.
 *
 * @param isoCountryCode region as ISO-3166-1 country code.
 *
 * @return example phone number. May return nil if the input region
 *         country code is invalid.
 */
- (nullable id<SINPhoneNumber>)exampleNumberForRegion:(NSString *)isoCountryCode;

/**
 * Checks whether input is a possible phone number, given a country
 * code where the number would be dialed from.
 *
 * Note that even if this method indicates that the input is a
 * possible phone number, it doesn't necessarily mean it's a valid
 * phone number. I.e. this is a less strict check.
 *
 * @param string input as an NSString*.
 *
 * @param isoCountryCode region as ISO-3166-1 country code where the
 *                    number will be dialed from.
 *
 * @param error that will be assigned if the string cannot be parsed
 *              as a phone number.
 */
- (BOOL)isPossibleNumber:(NSString *)string fromRegion:(NSString *)isoCountryCode error:(NSError **)error;

/**
 * Checks whether input is a possible phone number.
 *
 * Note that even if this method indicates that the input is a possible phone number,
 * it doesn't necessarily mean it's a valid phone number. I.e. this is a less strict
 * check.
 *
 * @param phoneNumber input as a parsed id<SINPhoneNumber>
 *
 * @param error that will be assigned if the string cannot be parsed
 *              as a phone number.
 *
 * @return indication of whether the input is a possible / viable phone number.
 */
- (BOOL)isPossibleNumber:(id<SINPhoneNumber>)phoneNumber error:(NSError **)error;

/**
 * Get a country calling code given a ISO-3166-1 country code.
 *
 * @param isoCountryCode region as ISO-3166-1 country.
 *
 * @return Country calling code corresponding to the given region. Return nil in case of failure.
 */
- (nullable NSNumber *)countryCallingCodeForRegion:(NSString *)isoCountryCode;

/**
 * Returns a region / country list structure that contains info on all
 * countries / regions available by NSLocale.ISOCountryCodes.  Each
 * entry in the list provides info such as ISO 3166-1 country code,
 * country dialing code, and country display name (according to the
 * given locale).
 *
 * @param locale locale that will be used to derive a display name
 *               for the region / country.
 */
- (id<SINRegionList>)regionListWithLocale:(NSLocale *)locale;

@end

/**
 * Returns a shared singleton instance.
 */
SIN_EXPORT SIN_EXTERN id<SINPhoneNumberUtil> SINPhoneNumberUtil();

/**
 * Create a new phone number util instance.
 *
 * NOTE: Consider using the shared singleton instance instead, to
 * avoid re-loading the underlying phonenumber metadata database for
 * each new instance).
 */
SIN_EXPORT SIN_EXTERN id<SINPhoneNumberUtil> SINPhoneNumberUtilCreate();

NS_ASSUME_NONNULL_END
