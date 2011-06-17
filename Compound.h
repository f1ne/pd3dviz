//
//  Compound.h
//  compound
//
//  Created by Rinat Enikeev on 6/17/11.
//  Copyright (c) 2011 f1ne labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface Compound : NSManagedObject {
@private
}
@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSManagedObject * elements;

@end
