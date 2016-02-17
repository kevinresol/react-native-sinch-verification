#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol SINRegionInfo <NSObject>

/**
 * ISO-3366-1 country code.
 *
 * Example: The ISO 3366-1 country for the United States is "US".
 */
@property (nonatomic, strong, readonly) NSString* isoCountryCode;

/**
 * Display name for country, given the locale that the SINRegionList
 * was created with.
 *
 * Example: Given the NSLocale "en_US", the display name would be
 *          "United States".
 */
@property (nonatomic, strong, readonly) NSString* countryDisplayName;

/**
 * ITU-T country calling code.
 *
 * Example: The ITU-T calling code for the region representing United
 *          States is 1.
 */
@property (nonatomic, strong, readonly) NSNumber* countryCallingCode;

@end

/**
 * SINRegionList provides a full list of countries / regions that can
 * be iterated, and it also provides lookup based on ISO 3366-1
 * country.
 */
@protocol SINRegionList <NSObject>

/**
 * Returns all region info entries (not sorted in any particular order).
 *
 * Example usage:
 *
 * // Get a list of regions sorted by display name (e.g. for
 * // displaying in a UITableView for example).
 *
 * NSLocale locale = [NSLocale currentLocale];
 * id<SINRegionList> regions = [SINPhoneNumberUtil() regionListWithLocale:locale];
 * NSSortDescriptor* sortDescriptor;
 * sortDescriptor = [[NSSortDescriptor alloc] initWithKey:@"countryDisplayName"
 *                                               ascending:YES];
 * NSArray<id<SINRegionInfo>>* sorted;
 * sorted = [regions.entries sortedArrayUsingDescriptors:@[ sortDescriptor ]];
 *
 */
@property (nonatomic, strong, readonly) NSArray<id<SINRegionInfo>>* entries;

/**
 * Get a display name for a particular ISO-3166-1 country code.
 *
 * @return A display name given an ISO-3166-1 countryCode. Returns
 *         empty string if no display name can be found.
 */
- (NSString*)displayNameForRegion:(NSString*)isoCountryCode;

/**
 * Get ITU-T country calling code by ISO-3166-1 country code. E.g. returns 1 for "US".
 *
 * @return An ITU-T country calling code. Returns nil if no calling code can be determined.
 */
- (nullable NSNumber*)countryCallingCodeForRegion:(NSString*)isoCountryCode;

@end

NS_ASSUME_NONNULL_END
