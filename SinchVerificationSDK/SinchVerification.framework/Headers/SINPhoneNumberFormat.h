/*
 * Copyright (c) 2016 Sinch AB. All rights reserved.
 *
 * See LICENSE file for license terms and information.
 */

#import <Foundation/Foundation.h>

/**

When formatting a phone number that is to be used to initiate a Sinch
Verification, the format `SINPhoneNumberFormatE164` should be used. The
other two formats (International and National) are primarily for
formatting for displaying in a GUI context.

For overview information on E.164 see https://en.wikipedia.org/wiki/E.164

*/
typedef NS_ENUM(NSInteger, SINPhoneNumberFormat) {
  SINPhoneNumberFormatE164,
  SINPhoneNumberFormatInternational,  // IMPORTANT: Use only for display / GUI purposes.
  SINPhoneNumberFormatNational,       // IMPORTANT: Use only for display / GUI purposes.
};
