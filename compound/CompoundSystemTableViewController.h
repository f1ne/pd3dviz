//
//  CompoundSystemTableViewController.h
//  compound
//
//  Created by Rinat Enikeev on 6/20/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CompoundSystemTableViewController : UITableViewController {
    NSMutableArray *listOfCompounds;   
}

@property (nonatomic, retain) NSManagedObject *compoundSystem;

@end
