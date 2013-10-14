IAPManager
==========

Yet Another simple in-app purchase interface for iOS.

A simple toolkit for non-renewables (a.k.a "Premium Features") with In-App Purchase.
The main goal is ease of use. Therefore, more complicated parts, like checking of receipts, are not provided.

Features
--------
- Simple setup
- Efficient one-line check if a product was purchased
- SKProducts to obtain prices
- Restoring purchases
- Uses block for callbacks

Requirements
------------
iOS 5 or above with ARC and StoreKit.framework.

How-to
------

1. Create your purchases in iTunes Connect. For details see the In-App Purchase Programming Guide.
2. Add StoreKit.framework to your project
3. Add `IAPManager.h` and `IAPManager.m` into your project, or use the [Pod](http://cocoapods.org) `IAPManager`.
4. Create your IAP UI
5. Use the methods of the `[IAPManager sharedIAPManager]` singleton:
    - Check if the App Store is available: `[[IAPManager sharedIAPManager] canPurchase]`
    - To obtain product information:
```objective-c
[[IAPManager sharedIAPManager] getProductsForIds:@[@"superpremiumversion"]
                                      completion:^(NSArray *products) {
                                          BOOL hasProducts = [products count] != 0;
                                          if(! hasProducts) {
                                              NSLog(@":(");
                                          }
                                          else {
                                              SKProduct *premium = products[0];
                                          
                                              NSNumberFormatter *numberFormatter = [[NSNumberFormatter alloc] init];                                                                                                                 [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
                                              [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
                                              [numberFormatter setLocale:premium.priceLocale];
                                              NSString *formattedPrice = [numberFormatter stringFromNumber:premium.price];
                                              NSLog(@"super premium: %@ for %@", premium.localizedTitle, formattedPrice);
                                          }
}];
```  
    - To purchase a product:
```objective-c
[[IAPManager sharedIAPManager] purchaseProductForId:@"superpremiumversion"
                                         completion:^(SKPaymentTransaction *transaction) {
                                             [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
                                             UIAlertView *thanks = [[UIAlertView alloc] initWithTitle:@"Thanks!"
                                                                                              message:@"The extra features are now available"
                                                                                             delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
                                             [thanks show];
                                         } error:^(NSError *err) {
                                             [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
                                         
                                             NSLog(@"An error occured while purchasing: %@", err.localizedDescription);
                                             // show an error alert to the user.
                                         }];
```                                         
      StoreKit will then ask the user if they want to purchase the product.

## Contact

![Travis CI build status](https://api.travis-ci.org/mruegenberg/IAPManager.png)

Bug reports and pull requests are welcome! Contact me via e-mail or just by opening an issue on GitHub.
