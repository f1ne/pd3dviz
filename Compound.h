//
//  Compound.h
//  compound
//
//  Created by Rinat Enikeev on 6/22/11.
//  Copyright (c) 2011 f1ne labs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface Compound : NSManagedObject {
@private
}
@property (nonatomic, retain) NSString * elementA;
@property (nonatomic, retain) NSString * elementB;
@property (nonatomic, retain) NSString * elementC;
@property (nonatomic, retain) NSString * elementD;
@property (nonatomic, retain) NSNumber * fractionA;
@property (nonatomic, retain) NSNumber * fractionB;
@property (nonatomic, retain) NSNumber * fractionC;
@property (nonatomic, retain) NSNumber * fractionD;

@end
