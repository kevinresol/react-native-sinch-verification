/*
 * Copyright (c) 2016 Sinch AB. All rights reserved.
 *
 * See LICENSE file for license terms and information.
 */

#import <Foundation/Foundation.h>
#import "SINExport.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * SINDeviceRegion is a helper class to get the current device's
 * ISO-3166-1 country code from the carrier information / SIM card.
*/
SIN_EXPORT
@interface SINDeviceRegion : NSObject

/**
 * Get the current device's current region ISO-3166-1 country code
 * based on: Primarily, the current SIM card's carrier country code
 * information if available.  Fallback to querying [NSLocale
 * currentLocale] for NSLocaleCountryCode.
 *
 * @return A ISO-3166-1 country code (uppercased)
 *
 */
+ (NSString*)currentCountryCode;

@end

NS_ASSUME_NONNULL_END
