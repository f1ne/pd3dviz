//
//  InsertCompoundViewController.m
//  compound
//
//  Created by Rinat Enikeev on 6/22/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#import "InsertCompoundViewController.h"


@implementation InsertCompoundViewController

@synthesize rootViewController=_rootViewController;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [_rootViewController release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(IBAction)addPressed:(id)sender
{
    NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
    [f setNumberStyle:NSNumberFormatterDecimalStyle];
    NSNumber *fracA = [f numberFromString:fractionA.text];
    NSNumber *fracB = [f numberFromString:fractionB.text];
    NSNumber *fracC = [f numberFromString:fractionC.text];
    NSNumber *fracD = [f numberFromString:fractionD.text];

    [f release];
    
    
    
    [self.rootViewController insertNewQuaternaryCompoundWithElementA:elementA.text fractionA:fracA elementB:elementB.text fractionB:fracB elementC:elementC.text fractionC:fracC  elementD:elementD.text fractionD:fracD];
}

@end
