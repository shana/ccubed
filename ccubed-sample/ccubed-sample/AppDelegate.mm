//
//  AppDelegate.m
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#import "AppDelegate.h"

#include "include/cef_application_mac.h"
#include "CallbackHandler.h"

@implementation AppDelegate

// Create the application on the UI thread.
- (void)createApp:(id)object {
  [NSApplication sharedApplication];
  [NSBundle loadNibNamed:@"MainMenu" owner:NSApp];

  // Set the delegate for application events.
  [NSApp setDelegate:self];
}

- (void)tryToTerminateApplication:(NSApplication*)app {
  CallbackHandler* handler = CallbackHandler::GetInstance();
  if (handler)
    handler->Close();
}

- (NSApplicationTerminateReply)applicationShouldTerminate:
      (NSApplication *)sender {
  return NSTerminateNow;
}

@end

@implementation CCubedSampleApplication
- (BOOL)isHandlingSendEvent {
  return handlingSendEvent_;
}

- (void)setHandlingSendEvent:(BOOL)handlingSendEvent {
  handlingSendEvent_ = handlingSendEvent;
}

- (void)sendEvent:(NSEvent*)event {
  CefScopedSendingEvent sendingEventScoper;
  [super sendEvent:event];
}

- (void)terminate:(id)sender {
  AppDelegate* delegate =
      static_cast<AppDelegate*>([NSApp delegate]);
  [delegate tryToTerminateApplication:self];
  // Return, don't exit. The application is responsible for exiting on its own.
}
@end
