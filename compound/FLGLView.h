//
//  FLGLView.h
//  compound
//
//  Created by Rinat Enikeev on 6/16/11.
//  Copyright 2011 f1ne labs. All rights reserved.
//

#import "Interfaces.hpp"
#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface FLGLView : UIView {
@private
    IApplicationEngine* m_applicationEngine;
    IRenderingEngine* m_renderingEngine;
    IResourceManager* m_resourceManager;
    EAGLContext* m_context;
    float m_timestamp;
}

- (void) drawView: (CADisplayLink*) displayLink;

@end
