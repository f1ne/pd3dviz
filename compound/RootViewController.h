//
//  RootViewController.h
//  compound
//
//  Created by Rinat Enikeev on 6/16/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DetailViewController;

#import <CoreData/CoreData.h>
#import "CompoundSystemTableViewController.h"
#import "InsertCompoundViewController.h"

@interface RootViewController : UITableViewController <NSFetchedResultsControllerDelegate> {

}


@property (nonatomic, retain) IBOutlet DetailViewController *detailViewController;

@property (nonatomic, retain) NSFetchedResultsController *fetchedResultsController;
@property (nonatomic, retain) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, retain) CompoundSystemTableViewController *compoundListViewController;

- (void)insertNewQuaternaryCompoundWithElementA:(NSString *)elA fractionA:(NSNumber *)frA elementB:(NSString *)elB fractionB:(NSNumber *)frB elementC:(NSString *) elC fractionC:(NSNumber *)frC elementD:(NSString *)elD fractionD:(NSNumber *)frD;

@end
