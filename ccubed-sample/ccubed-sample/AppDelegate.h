//
//  AppDelegate.h
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "CCubedApp.h"

@interface AppDelegate : NSObject
- (void)createApp:(id)object;
@end


@interface CCubedSampleApplication : NSApplication<CefAppProtocol> {
@private
    BOOL handlingSendEvent_;
}
@end