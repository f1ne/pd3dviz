//
//  InsertCompoundViewController.h
//  compound
//
//  Created by Rinat Enikeev on 6/22/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RootViewController;

@interface InsertCompoundViewController : UIViewController {
    IBOutlet UITextField *elementA;
    IBOutlet UITextField *elementB;
    IBOutlet UITextField *elementC;
    IBOutlet UITextField *elementD;
    IBOutlet UITextField *fractionA;
    IBOutlet UITextField *fractionB;
    IBOutlet UITextField *fractionC;
    IBOutlet UITextField *fractionD;
}

@property (nonatomic, assign) IBOutlet RootViewController *rootViewController;

-(IBAction)addPressed:(id)sender;

@end
