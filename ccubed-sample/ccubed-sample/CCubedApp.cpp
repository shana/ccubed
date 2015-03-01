//
//  CCubedApp.cpp
//  ccubed-sample
//
//  Created by Shawn White on 31/01/15.
//  Copyright (c) 2015 Andreia Gaita. All rights reserved.
//

#include "CCubedApp.h"

#include "RequestHandler.h"

void
CCubedApp::Initialize(int argc, char* argv[])
{
    // Provide CEF with command-line arguments.
    CefMainArgs main_args(argc, argv);
    
    // SimpleApp implements application-level callbacks. It will create the first
    // browser instance in OnContextInitialized() after CEF has initialized.

    // Specify CEF global settings here.
    CefSettings settings;
    
    // Initialize CEF for the browser process.
    CefInitialize(main_args, settings, GetCef().get(), NULL);
    
    CefRegisterSchemeHandlerFactory("client", "ccubed", new ClientSchemeHandlerFactory());

}

bool
CCubedApp::Run()
{
    // Run the CEF message loop. This will block until CefQuitMessageLoop() is
    // called.
    CefRunMessageLoop();

    return true;
}

void
CCubedApp::Shutdown()
{
    // Shut down CEF.
    CefShutdown();
}