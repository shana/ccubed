//
//  main.m
//  ccubed-sample
//
//  Created by Andreia Gaita on 1/31/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"

#include "CCubedApp.h"
#include "File.h"

// Entry point function for the browser process.
int main(int argc, char* argv[]) {

	NSString* dirpath = [[NSFileManager defaultManager] currentDirectoryPath];
	//dirpath = [dirpath stringByDeletingLastPathComponent];
	
	dirpath = [dirpath stringByAppendingPathComponent:@"ccubed-sample.app"];
	dirpath = [dirpath stringByAppendingPathComponent:@"Contents"];
	dirpath = [dirpath stringByAppendingPathComponent:@"Resources"];

	File::SetExecDir([dirpath UTF8String]);

    CCubedApp* app = new CCubedApp();
    app->Initialize(argc, argv);
    
    // Initialize the SimpleApplication instance.
    [CCubedSampleApplication sharedApplication];
	
    // Create the application delegate.
    NSObject* delegate = [[AppDelegate alloc] init];
    [delegate performSelectorOnMainThread:@selector(createApp:) withObject:nil
                            waitUntilDone:NO];
    
    
    app->Run();

    app->Shutdown();
    
    return 0;
}