//
//  FLGLView.m
//  compound
//
//  Created by Rinat Enikeev on 6/16/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#import "FLGLView.h"

@implementation FLGLView

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect) frame
{
    self = [super initWithFrame:frame];
	if (self) {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        self.multipleTouchEnabled = YES;
        eaglLayer.opaque = TRUE;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            [self release];
            return nil;
        }
        m_resourceManager = CreateResourceManager();
        m_renderingEngine = ES2::CreateRenderingEngine(m_resourceManager);
        
        m_applicationEngine = tetraCompound::CreateApplicationEngine(m_renderingEngine, m_resourceManager);
        
        [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        int width = CGRectGetWidth(frame);
        int height = CGRectGetHeight(frame);
        m_applicationEngine->Initialize(width, height);
        
        [self drawView:nil];
        m_timestamp = CACurrentMediaTime();
        
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    }
    
    return self;
}

- (void) drawView: (CADisplayLink*) displayLink
{
    if (displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_applicationEngine->UpdateAnimation(elapsedSeconds);
    }
    
    m_applicationEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event
{
    
    UITouch* touch1  = [[touches allObjects] objectAtIndex:0];
    CGPoint finger1Location  = [touch1 locationInView: self];
    
    if ([[touches allObjects] count] == 1) {
        
        m_applicationEngine->OnFingerDown(ivec2(finger1Location.x, finger1Location.y));
    } 
}

- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch1  = [[touches allObjects] objectAtIndex:0];
    
    CGPoint previous  = [touch1 previousLocationInView: self];
    CGPoint current = [touch1 locationInView: self];
    
    if ([[touches allObjects] count] == 1) {
        m_applicationEngine->OnFingerMove(ivec2(previous.x, previous.y),
                                          ivec2(current.x, current.y));
        
    } 
}

- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch1  = [[touches allObjects] objectAtIndex:0];
    CGPoint finger1Location  = [touch1 locationInView: self];
    
    if ([[touches allObjects] count] == 1) {
        
        m_applicationEngine->OnFingerUp(ivec2(finger1Location.x, finger1Location.y));
        
    }
}



@end
