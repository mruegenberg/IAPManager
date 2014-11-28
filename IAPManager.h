//
//  IAPManager.h
//  Classes
//
//  Created by Marcel Ruegenberg on 22.11.12.
//  Copyright (c) 2012 Dustlab. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <StoreKit/StoreKit.h>


#if !TARGET_OS_IPHONE
#ifndef UIApplicationWillResignActiveNotification
#define UIApplicationWillResignActiveNotification NSApplicationWillResignActiveNotification
#endif
#endif

typedef void(^PurchaseCompletionBlock)(SKPaymentTransaction *transaction);
typedef void(^ProductsCompletionBlock)(NSArray *products);
typedef void(^ErrorBlock)(NSError *error);
typedef void(^PurchasedProductsChanged)(void);
typedef void(^RestorePurchasesCompletionBlock)(void);

// use SIMULATE_PURCHASES to prevent any actual purchasing from happening, i.e
// if a user "buys" an item, the transaction immediately succeeds, without any communication with the App Store happening.
// #define SIMULATE_PURCHASES

#ifdef SIMULATE_PURCHASES
#warning In-App Purchase is only simulated!
#endif

/// A simple toolkit for non-renewables (a.k.a "Premium Features") with In-App Purchase.
/// The main goal is ease of use. Therefore, more complicated parts, like checking of receipts, are not provided.
@interface IAPManager : NSObject

+ (IAPManager *)sharedIAPManager;

- (BOOL)hasPurchased:(NSString *)productId;

#pragma mark Product Information

/// passes a set of products to the completion block
- (void)getProductsForIds:(NSArray *)productIds completion:(ProductsCompletionBlock)completionBlock __attribute__((deprecated));

/**
 * passes a set of products to the completion block
 * if an error occurs, `err` is called with the error object (which is potentially nil)
*/
- (void)getProductsForIds:(NSArray *)productIds completion:(ProductsCompletionBlock)completionBlock error:(ErrorBlock)errorBlock;

#pragma mark Purchase

- (void)restorePurchases;

- (void)restorePurchasesWithCompletion:(RestorePurchasesCompletionBlock)completionBlock;

- (void)restorePurchasesWithCompletion:(RestorePurchasesCompletionBlock)completionBlock error:(ErrorBlock)err;

- (void)purchaseProduct:(SKProduct *)product completion:(PurchaseCompletionBlock)completionBlock error:(ErrorBlock)err;

/// if an error occurs, `err` is called with the error object (which is potentially nil)
- (void)purchaseProductForId:(NSString *)productId completion:(PurchaseCompletionBlock)completionBlock error:(ErrorBlock)err;

/// Checks whether purchases are allowed by the App Store. This does not check whether there is a connection to the internet.
- (BOOL)canPurchase;

#pragma mark Observation

/// add a callback that should be called if a new product is purchased.
/// use as the context object an object that you can use to remove the observer again.
- (void)addPurchasesChangedCallback:(PurchasedProductsChanged)callback withContext:(id)context;

- (void)removePurchasesChangedCallbackWithContext:(id)context;

@end
